/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_string.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/29 15:35:13 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_strlen_test(const char *s)
{
	//return (ft_strlen(s) != strlen(s));
	size_t expected = strlen(s);
    size_t actual = ft_strlen(s);

    if (expected != actual)
    {
        printf("FAIL: strlen(\"%s\") expected %zu, got %zu\n", s, expected, actual);
        return (1);
    }
    return (0);
}

static int run_strchr_test(const char *s, int c)
{
	char *expected = strchr(s, c);
	char *actual = ft_strchr(s, c);
	
	if (actual != expected)
	{
		printf("FAIL: strchr(\"%s\", \"%c\") expected %s(%p), got %s(%p)\n", s, c, expected, expected, actual, actual);
		return (1); // false
	}
	return (0);
}
static int run_strrchr_test(const char *s, int c)
{
	char *expected = strrchr(s, c);
	char *actual = ft_strrchr(s, c);
	
	if (actual != expected)
	{
		printf("FAIL: strchr(\"%s\", \"%c\") expected %s(%p), got %s(%p)\n", s, c, expected, expected, actual, actual);
		return (1); // false
	}
	return (0);
}
// static int run_strncmp_test(const char *s1, const char *s2, size_t n)
// static int run_strnstr_test(const char *haystack, const char *needle, size_t len)

int test_ft_strlen(void)
{
	int			i = 0;
	const char	*tests[] = {"", "abc", "42 network", "\n", " ", 0};
	const char  arr[] = {'H', 'e', '\0', 'l', 'l','o'};

	i = 0;
    while (tests[i])
    {
        if (run_strlen_test(tests[i]))
            return (1); // fail
        i++;
    }
	if (run_strlen_test(arr + 2))
            return (1); // fail
    return (0); // pass
}

int test_ft_strchr(void)
{
	int i;
	const char *str[] = {"Hello", "Network42", "not_found", "First_char", "last_chaR",0};
	const char c[] = {'l', '4', '-', 'F', 'R'};

	i = 0;
	while (str[i])
	{
		if (run_strchr_test(str[i], c[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}

int test_ft_strrchr(void)
{
	int i;
	const char *str[] = {"Hello", "Network42", "not_found", "First_char", "last_chaR",0};
	const char c[] = {'l', '4', '-', 'F', 'R'};

	i = 0;
	while (str[i])
	{
		if (run_strrchr_test(str[i], c[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}