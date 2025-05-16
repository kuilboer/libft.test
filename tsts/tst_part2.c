/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_part2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:27:39 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/16 19:15:39 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "tsts.h"
//#include "tsts.h"

// Trusted reference function (from GLib or your own implementation)
//char *glib__substr(const char *s, unsigned int start, size_t len);  // assume this exists

static int assert_split(char **actual, const char **expected)
{
    int i = 0;
    while (expected[i] || actual[i])
    {
        if (!actual[i] || !expected[i])
        {
            printf("FAIL: Length mismatch\n");
            return 1;
        }
        if (strcmp(actual[i], expected[i]) != 0)
        {
            printf("FAIL: Expected '%s', got '%s'\n", expected[i], actual[i]);
            return 1;
        }
        i++;
    }
    return 0;
}

static void free_split(char **arr)
{
    if (!arr) return;
	printf("elements");
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
		printf("array");
    free(arr);
}

static int run_strtrim_test(const char *s1, const char *set, const char *expected)
{
	//char *expected = ref__strtrim(s1, set);
	char *actual = ft_strtrim(s1, set);
	int failed = 0;

	printf("expected = %s\nactual = %s\n\n", expected, actual);

	if ((expected == NULL && actual != NULL) ||
		(expected != NULL && actual == NULL) ||
		(expected && actual && strcmp(expected, actual) != 0))
	{
		printf("FAIL: ft_strtrim(\"%s\", \"%s\")\n",
			s1 ? s1 : "NULL", set ? set : "NULL");
		printf("   expected: \"%s\"\n", expected ? expected : "NULL");
		printf("   got     : \"%s\"\n", actual ? actual : "NULL");
		failed = 1;
	}

	//free(expected);
	free(actual);
	return failed;
}

static int run_strjoin_test(const char *s1, const char *s2)
{
	char *expected = glib__strjoin(s1, s2);
	char *actual = ft_strjoin(s1, s2);
	int failed = 0;

	if ((expected == NULL && actual != NULL) ||
		(expected != NULL && actual == NULL) ||
		(expected && actual && strcmp(expected, actual) != 0))
	{
		printf("FAIL: ft_strjoin(\"%s\", \"%s\")\n", 
			s1 ? s1 : "NULL", s2 ? s2 : "NULL");
		printf("   expected: \"%s\"\n", expected ? expected : "NULL");
		printf("   got     : \"%s\"\n", actual ? actual : "NULL");
		failed = 1;
	}
	free(expected);
	free(actual);
	return failed;
}

static int run_substr_test(const char *input, unsigned int start, size_t len)
{
	char *expected = glib__substr(input, start, len);  // trusted
	char *actual = ft_substr(input, start, len);       // your implementation
	int failed = 0;

	if ((expected == NULL && actual != NULL) ||
		(expected != NULL && actual == NULL) ||
		(expected && actual && strcmp(expected, actual) != 0))
	{
		printf("FAIL: ft_substr(\"%s\", %u, %zu)\n", input, start, len);
		printf("   expected: \"%s\"\n", expected ? expected : "NULL");
		printf("   got     : \"%s\"\n", actual ? actual : "NULL");
		failed = 1;
	}
	free(expected);
	free(actual);
	return failed;
}

int test_ft_split(void)
{
    int failed = 0;

    struct {
        const char *input;
        char delim;
        const char *expected[10];
    } tests[] = {
        // {"a,b,c", ',', {"a", "b", "c", NULL}},
        // {",a,,b,", ',', {"a", "b", NULL}},
        // {",,,", ',', {NULL}},
        // {"abc", ',', {"abc", NULL}},
        // {"", ',', {NULL}},
		{"\0aaa\0bb", '\0', {NULL}},
        {NULL, ',', {NULL}},
    };

    for (int t = 0; tests[t].input != NULL || tests[t].expected[0] != NULL; t++) {
        printf("Testing: '%s'\n", tests[t].input ? tests[t].input : "(null)");
        char **actual = ft_split(tests[t].input, tests[t].delim);
        if (assert_split(actual, tests[t].expected)) {
            printf("Test %d failed.\n\n", t);
            failed = 1;
        } else {
            printf("PASS\n\n");
        }
        free_split(actual);
    }

    return failed;
}

int test_ft_strtrim(void)
{
	struct {
        const char *strs;
        const char *sets;
		const char *expected;
        //const char *expected;
    } tests[] = {
        {"  hello  ", " ", "hello"},
		{" . abc", " ", ". abc"},
		{"tetettsetlerte", "te", "setler"},
		{"lorem \n ipsum \t dolor \n sit \t amet", " ", "lorem \n ipsum \t dolor \n sit \t amet"},
		{"lorem ipsum dolor sit amet", "te", "lorem ipsum dolor sit am"},
		{"  \t \t \n   \n\n\n\t", "", "  \t \t \n   \n\n\n\t" },
		{"   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ", " \t\n", "Hello \t  Please\n Trim me !"},
		{"", "", ""},
		{NULL, "-", NULL},
		{"abc", NULL, NULL},
		{NULL, NULL, NULL},
    };

	for (int i = 0; tests[i].strs || tests[i].sets; i++)
	{
		if (run_strtrim_test(tests[i].strs, tests[i].sets, tests[i].expected))
			return 1;
	}

	//Extra expliciete NULL-tests
	// if (run_strtrim_test(NULL, "-"))
	// 	return 1;
	// if (run_strtrim_test("abc", NULL))
	// 	return 1;
	// if (run_strtrim_test(NULL, NULL))
	// 	return 1;

	return 0;
}

int test_ft_strjoin(void)
{
	const char *inputs1[] = {
		"Hello", "", "The quick ", "Only one", NULL, NULL
	};
	const char *inputs2[] = {
		" World", "", "brown fox", NULL, "Still valid", NULL
	};

	for (int i = 0; inputs1[i] || inputs2[i]; i++)
	{
		if (run_strjoin_test(inputs1[i], inputs2[i]))
			return 1;
	}
	if (run_strjoin_test(NULL, "non-null"))    // Expliciete edge cases waarbij input ontbreekt;
		return 1;

	if (run_strjoin_test("non-null", NULL))
		return 1;

	if (run_strjoin_test(NULL, NULL))
		return 1;
	return 0;
}

int test_ft_substr(void)
{
	const char *inputs[] = {
		"Hello World",
		"Hello World",
		"Hello World",
		"Hello",
		"Hello",
		"Hello",
		NULL
	};
	unsigned int starts[] = {0, 6, 6, 10, 0, 2};
	size_t lens[]         = {5, 5, 100, 5, 0, 1};

	int i = 0;
	while (inputs[i])
	{
		if (run_substr_test(inputs[i], starts[i], lens[i]))
			return 1; // fail
		i++;
	}
	if (run_substr_test(NULL, 0, 5)) // NULL input
		return 1;

	if (run_substr_test("Ends here", strlen("Ends here"), 5)) // start == strlen
		return 1;

	if (run_substr_test("€uro", 0, 1)) // UTF-8 start
		return 1;

	if (run_substr_test("  hello  ", 2, 5)) // trimming test
		return 1;

	return 0; // all passed
}