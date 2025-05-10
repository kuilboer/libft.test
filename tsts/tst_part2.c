/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_part2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:27:39 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/09 19:57:24 by okuilboe      ########   odam.nl         */
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

void print_split(char **split)
{
	int i = 0;

	if (!split)
	{
		printf("(null)\n");
		return;
	}

	while (split[i])
	{
		printf("[%d] \"%s\"\n", i, split[i]);
		i++;
	}
	printf("[end]\n");
}

static int compare_split_arrays(char **a, char **b)
{
	int i = 0;

	while (a && b && a[i] && b[i])
	{
		if (!a[i] || !b[i])
		{
			printf("NULL pointer at compare[%d]: a=%p, b=%p\n", i, (void *)a[i], (void *)b[i]);
			return 1;
		}
		printf("compare[%d]: a=\"%s\", b=\"%s\"\n", i, a[i], b[i]);
		if (strcmp(a[i], b[i]) != 0)
			return 1;
		i++;
	}
	if ((a && a[i]) || (b && b[i]))
		return 1; // arrays are of different length
	return 0;
}

static int run_split_test(const char *s, char delim)
{
	// printf("Testing: \"%s\"\n", s ? s : "NULL");
		
	char **expected = ref__split(s, delim);
	if (!expected)
	{
		printf("ref__split returned NULL ❌\n");
		return 1;
	}

	printf("expected[0] = %p\n", (void *)expected[0]);
	for (int j = 0; j < 4; j++)
		printf("expected[%d] = %s\n", j, expected[j] ? expected[j] : "(null)");
	
	char **actual = ft_split(s, delim);
	if (!actual)
	{
   	 printf("FAIL: ft_split(\"%s\", '%c') ➜ returned NULL unexpectedly\n", s, delim);
   	 return 1;
	}
	printf("actual[0] = %p\n", (void *)actual[0]);
	for (int j = 0; j < 4; j++)
		printf("actual[%d] = %s\n", j, actual[j] ? actual[j] : "(null)");

	printf("\nStart compare.\n");
	int failed = compare_split_arrays(expected, actual);
	printf("End compare.\n");
	if (failed)
	{
		printf("FAIL: ft_split(\"%s\", '%c')\n", s ? s : "NULL", delim);
		printf("Expected:\n");
		print_split(expected);
		printf("Got:\n");
		print_split(actual);
	}

	// free both
	if (expected)
	{
		for (int i = 0; expected[i]; i++) free(expected[i]);
		free(expected);
	}
	if (actual)
	{
		for (int i = 0; actual[i]; i++) free(actual[i]);
		free(actual);
	}

	return failed;
}


static int run_strtrim_test(const char *s1, const char *set)
{
	char *expected = ref__strtrim(s1, set);
	char *actual = ft_strtrim(s1, set);
	int failed = 0;

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

	free(expected);
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
	const char *inputs[] = {
		"a,b,c",
		",,a,,b,",
		"",
		",,,",
		"abc",
		"   split   this please  ",
		NULL
	};

	char delimiters[] = {
		',',
		',',
		',',
		',',
		'x',
		' ',
	};
	
	for (int i = 0; inputs[i]; i++)
	{
		printf("Testing: \"%s\"\n", inputs[i] ? inputs[i] : "NULL");
		if (run_split_test(inputs[i], delimiters[i]))
			return 1;
	}

	// NULL input test
	if (run_split_test(NULL, ','))
		return 1;

	return 0;
}

int test_ft_strtrim(void)
{
	const char *inputs[] = {
		"  hello  ",
		"---abc---",
		"abc",
		"aaaaa",
		"",
		NULL
	};

	const char *sets[] = {
		" ",
		"-",
		"x",
		"a",
		"a",
		NULL
	};

	for (int i = 0; inputs[i] || sets[i]; i++)
	{
		if (run_strtrim_test(inputs[i], sets[i]))
			return 1;
	}

	// Extra expliciete NULL-tests
	if (run_strtrim_test(NULL, "-"))
		return 1;
	if (run_strtrim_test("abc", NULL))
		return 1;
	if (run_strtrim_test(NULL, NULL))
		return 1;

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