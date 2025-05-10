/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 16:07:29 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/08 18:23:12 by okuilboe      ########   odam.nl         */
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
		test_ft_atoi,
		test_ft_strdup,
		test_ft_strlen,
		test_ft_strchr,
		test_ft_strchr,
		test_ft_strncmp,
		test_ft_strnstr,
		test_ft_strlcat,
		test_ft_strlcpy,
	};
	const char *string_names[] = {
		"ft_atoi",
		"ft_strdup",
		"ft_strlen",
		"ft_strchr",
		"ft_strrchr",
		"ft_strncmp",
		"ft_strnstr",
		"ft_strlcat",
		"ft_strlcpy"
	};

	t_test_fn mem_tests[] = {
		test_ft_bzero,
		test_ft_calloc,
		test_ft_memcmp,
		test_ft_memcpy,
		test_ft_memmove,
		test_ft_memset,
	};
	const char *mem_names[] = {
		"ft_bzero",
		"ft_calloc",
		"ft_memcmp",
		"ft_memcpy",
		"ft_memmove",
		"ft_memset",
	};

	t_test_fn part2_tests[] = {
		test_ft_substr,
		test_ft_strjoin,
		test_ft_strtrim,
		test_ft_split,
	};
	const char *part2_names[] = {
		"ft_substr",
		"ft_strjoin",
		"ft_strtrim",
		"test_ft_split"
	};

	run_tests("Character Class Tests", char_tests, char_names, sizeof(char_tests)/sizeof(char_tests[0]));
	run_tests("String Functions Tests", string_tests, string_names, sizeof(string_tests)/sizeof(string_tests[0]));
	run_tests("Memory Ops. Functions Tests", mem_tests, mem_names, sizeof(mem_tests)/sizeof(mem_tests[0]));
	run_tests("Part2 Functions Tests", part2_tests, part2_names, sizeof(part2_tests)/sizeof(part2_tests[0]));
	return 0;
}
