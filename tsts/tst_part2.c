/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_part2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:27:39 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/17 21:56:58 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "utils.h"
#include "tsts.h"



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
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

static int run_strtrim_test(const char *s1, const char *set, const char *expected)
{
	//char *expected = ref__strtrim(s1, set);
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

static int run_itoa_test(int n, const char *exp)
{
	char	*actual = ft_itoa(n);
	int		n_len = ft_strlen(actual);
	int		exp_len = ft_strlen(exp);

	if (n_len == exp_len && !(ft_strncmp(exp, actual, exp_len)))
		return (0); // pass

	printf("\nInput int: \t%d\nExpected: \t%s\nActual: \t%s\n\n", n, exp, actual);
	printf("exp_len = %d \nact_len = %d\n", exp_len, n_len);
	printf("ft_strncmp = %d\n\n", ft_strncmp(exp, actual, exp_len));
	free(actual);
	return (1); //fail
}

static int run_strmapi_test(const char *input, char (*f)(unsigned int, char), const char *expected)
{
	char *result = ft_strmapi(input, f);
	int success = strcmp(result, expected) == 0;
	if (!success)
	{
		printf("❌ ft_strmapi(\"%s\") with mapper failed\nExpected: \"%s\"\nGot     : \"%s\"\n",
			input, expected, result);
	}
	free(result);
	return !success; // return 0 if OK, 1 if failed
}

static int run_striteri_test(char *input, void (*f)(unsigned int, char *), const char *expected)
{
	char buffer[100];
	strcpy(buffer, input);
	ft_striteri(buffer, f);
	if (strcmp(buffer, expected) == 0)
		return (0); //Success
	else
		printf("❌ Failed: got \"%s\", expected \"%s\"\n", buffer, expected);
	return (1); // Failure
}

static int run_putchar_fd_test(char input_char)
{
	int		fd;
	char	read_buf[2] = {0}; // One char + null terminator
	char	*tmp_file = "tmp_putchar_fd.txt";

	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);

	ft_putchar_fd(input_char, fd);
	lseek(fd, 0, SEEK_SET);
	read(fd, read_buf, 1);
	close(fd);
	unlink(tmp_file);

	if (read_buf[0] != input_char)
		return (1);
	return (0);
}

static int run_putstr_fd_test(const char *input)
{
	const char	*tmp_file = "tmp_putstr_fd.txt";
	char		read_buf[1024] = {0}; // Buffer to read back the file
	int			fd;
	ssize_t		bytes_read;

	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);

	ft_putstr_fd((char *)input, fd); // Cast to match ft_putstr_fd prototype
	lseek(fd, 0, SEEK_SET);
	bytes_read = read(fd, read_buf, sizeof(read_buf) - 1);
	close(fd);
	unlink(tmp_file);

	if (bytes_read < 0)
		return (1);

	read_buf[bytes_read] = '\0'; // Null-terminate

	if (strcmp(read_buf, input) != 0)
		return (1);

	return (0);
}

static int run_putendl_fd_test(const char *input)
{
	const char	*tmp_file = "tmp_putendl_fd.txt";
	char		read_buf[1024] = {0}; // Buffer to read output
	char		expected_buf[1024] = {0};
	int			fd;
	ssize_t		bytes_read;

	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);

	ft_putendl_fd((char *)input, fd); // Cast for compatibility
	lseek(fd, 0, SEEK_SET);
	bytes_read = read(fd, read_buf, sizeof(read_buf) - 1);
	close(fd);
	unlink(tmp_file);

	if (bytes_read < 0)
		return (1);

	read_buf[bytes_read] = '\0';

	// Create expected output (input + newline)
	snprintf(expected_buf, sizeof(expected_buf), "%s\n", input);

	if (strcmp(read_buf, expected_buf) != 0)
		return (1);

	return (0);
}

static int run_putnbr_fd_test(int input)
{
	const char	*tmp_file = "tmp_putnbr_fd.txt";
	char		read_buf[64] = {0};    // Enough to hold any int
	char		expected_buf[64] = {0};
	int			fd;
	ssize_t		bytes_read;

	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);

	ft_putnbr_fd(input, fd);

	lseek(fd, 0, SEEK_SET);
	bytes_read = read(fd, read_buf, sizeof(read_buf) - 1);
	close(fd);
	unlink(tmp_file);

	if (bytes_read < 0)
		return (1);

	read_buf[bytes_read] = '\0';
	sprintf(expected_buf, "%d", input);

	if (strcmp(read_buf, expected_buf) != 0)
		return (1);

	return (0);
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
        char **actual = ft_split(tests[t].input, tests[t].delim);
        if (assert_split(actual, tests[t].expected)) {
            printf("Test %d failed.\n\n", t);
            failed = 1;
        } else {
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

int	test_ft_itoa(void)
{
	struct {
        const int numbers;
		const char *expected;
    } tests[] = {
		{123, "123"},
        {1234567890, "1234567890"},
		{0, "0"},
		{-10, "-10"},
		{INT_MIN, "-2147483648"},
		{INT_MAX, NULL},
    };

	for (int i = 0; !(tests[i].numbers == INT_MAX && tests[i].expected == NULL) ; i++)
	{
		if (run_itoa_test(tests[i].numbers, tests[i].expected))
			return 1;
	}
	return (0);

}

int test_ft_strmapi(void)
{
	int fails = 0;

	fails += run_strmapi_test("hello", identity, "hello");
	fails += run_strmapi_test("hello", uppercase_even, "HeLlO");
	fails += run_strmapi_test("abcde", index_to_char, "01234");
	fails += run_strmapi_test("test", constant_Z, "ZZZZ");
	fails += run_strmapi_test("", identity, "");

	return fails;
}

int test_ft_striteri(void)
{
	int fails = 0;

	fails += run_striteri_test("abc", to_upper, "ABC");
	fails += run_striteri_test("abcde", upper_even, "AbCdE");
	fails += run_striteri_test("abc", add_index_to_char, "ace");
	fails += run_striteri_test("abc", noop, "abc");
	fails += run_striteri_test("", to_upper, "");

	// Optionally test NULL input
	// ft_striteri(NULL, to_upper);  // Should do nothing / not crash

	return (fails);
}

int test_ft_putchar_fd(void)
{
	int result = 0;

	char test_chars[] = {'A', '\n', 'z', '0', 127}; // Include normal, newline, edge-case ASCII
	int num_tests = sizeof(test_chars) / sizeof(test_chars[0]);

	for (int i = 0; i < num_tests; i++)
	{
		if (run_putchar_fd_test(test_chars[i]) != 0)
		{
			printf("❌ Test %d failed: input='%c' (ASCII %d)\n", i, test_chars[i], test_chars[i]);
			result = 1;
		}
	}

	return result;
}

int test_ft_putstr_fd(void)
{
	int result = 0;

	const char *tests[] = {
		"Hello, world!",
		"",
		"Line1\nLine2\n",
		"💡 Unicode? Nope. Just plain C.",
		"0123456789",
		NULL
	};

	for (int i = 0; tests[i] != NULL; i++)
	{
		if (run_putstr_fd_test(tests[i]) != 0)
		{
			printf("❌ Test %d failed: \"%s\"\n", i, tests[i]);
			result = 1;
		}
	}

	return result;
}

int test_ft_putendl_fd(void)
{
	int result = 0;

	const char *tests[] = {
		"Hello, newline!",
		"",
		"Multiline?\nNope, just newline at the end.",
		"Line without newline",
		NULL
	};

	for (int i = 0; tests[i] != NULL; i++)
	{
		if (run_putendl_fd_test(tests[i]) != 0)
		{
			printf("❌ Test %d failed: \"%s\"\n", i, tests[i]);
			result = 1;
		}
	}

	return result;
}

int test_ft_putnbr_fd(void)
{
	int result = 0;

	int tests[] = {
		0,
		1,
		-1,
		42,
		-42,
		2147483647,
		-2147483648
	};

	int num_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < num_tests; i++)
	{
		if (run_putnbr_fd_test(tests[i]) != 0)
		{
			printf("❌ Test %d failed: input=%d\n", i, tests[i]);
			result = 1;
		}
	}

	return result;
}