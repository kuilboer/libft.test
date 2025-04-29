/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 16:07:29 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/29 17:59:14 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

void	run_tests(const char *group_name, t_test_fn *tests, const char **names, int count)
{
    int passed = 0;
    int failed = 0;

    printf("\n=== %s ===\n", group_name);

    for (int i = 0; i < count; i++)
    {
        int result = tests[i]();
        if (result == 0)
        {
            printf("PASS: %15s ✅\n", names[i]);
            passed++;
        }
        else
        {
            printf("FAIL: %15s ❌\n", names[i]);
            failed++;
        }
    }

    printf("\nResult for %s: %d passed, %d failed\n", group_name, passed, failed);
}

int main(void)
{
    t_test_fn char_tests[] = {
        test_ft_isalpha,
        test_ft_isdigit,
        test_ft_isalnum,
        test_ft_isascii,
        test_ft_isprint,
		test_ft_tolower,
		test_ft_toupper
    };
    const char *char_names[] = {
        "ft_isalpha", 
		"ft_isdigit", 
		"ft_isalnum", 
		"ft_isascii", 
		"ft_isprint",
		"ft_tolower",
		"ft_toupper"
    };

    t_test_fn string_tests[] = {
        test_ft_strlen,
		test_ft_strchr,
        test_ft_strchr,
        test_ft_strncmp,
    };
    const char *string_names[] = {
        "ft_strlen",
		"ft_strchr",
        "ft_strrchr",
        "ft_strncmp",
    };

    run_tests("Character Class Tests", char_tests, char_names, sizeof(char_tests)/sizeof(char_tests[0]));
    run_tests("String Functions Tests", string_tests, string_names, sizeof(string_tests)/sizeof(string_tests[0]));

    return 0;
}
