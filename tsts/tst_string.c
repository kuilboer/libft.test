/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_string.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/28 17:16:56 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_strlen_test(const char *s)
{
	return (ft_strlen(s) != strlen(s));
}

// static int run_strchr_test(const char *s, int c)
// static int run_strncmp_test(const char *s1, const char *s2, size_t n)
// static int run_strnstr_test(const char *haystack, const char *needle, size_t len)

int test_ft_strlen(void)
{
	int			i = 0;
	const char	*tests[] = {"", "abc", "42 network", NULL, "\n", " "};
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

// int test_ft_strlen(void)
// {
//     const char *tests[] = {"", "Hello", "Test123", "\n", " ", 0};

//     for (int i = 0; tests[i]; i++)
//     {
//         if (ft_strlen(tests[i]) != strlen(tests[i]))
//             return (1);
//     }
//     return (0);
// }

