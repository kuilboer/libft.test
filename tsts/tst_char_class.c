/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_char_class.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 14:49:22 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/27 17:51:30 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>    // For system functions
#include "libft.h"    // Your functions

/* The typedef for this generalized function is set in the header file. 
(typedef int (*char_test_fn)(int);) */

int run_char_test(char_test_fn ft_func, char_test_fn sys_func, const char *name)
{
	int failed = 0;

	for (int c = -128; c <= 127; c++)
	{
		int expected = sys_func(c) != 0; // normalize to 0/1
		int actual = ft_func(c) != 0;

		if (expected != actual)
		{
			//printf("  FAIL: %s(%d) system=%d ft=%d\n", name, c, expected, actual);
			//failed = 1;
			return (1);
		}
	}

	return (0);
	// if (!failed)
	// 	printf("PASS: %s ✅\n", name);
	// else
	// 	printf("FAILURES in %s ❌\n", name);
}

