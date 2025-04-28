/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_char_class.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 14:49:22 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/28 17:26:28 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_char_test(t_char_test_fn ft_func, t_char_test_fn sys_func, char mode)
{
    for (int c = -128; c <= 127; c++)
    {
        if (mode == 'b')
		{
			if ((!!ft_func(c)) != (!!sys_func(c)))
            	return (1); // fail
		}
		else if (mode == 'v' )
		{
			if (ft_func(c) != sys_func(c))
			{
				printf("\t ft %c(%i) != sys %c(%i) for input = %d\n", ft_func(c), ft_func(c), sys_func(c), sys_func(c), c);
				return (1);
			}
		}
		else
		{
			printf("Wrong mode");
			return (1);
		}
    }
    return (0); // pass
}

int test_ft_isalnum(void) { return run_char_test(ft_isalnum, isalnum, 'b'); }
int test_ft_isalpha(void) { return run_char_test(ft_isalpha, isalpha, 'b'); }
int test_ft_isascii(void) { return run_char_test(ft_isascii, isascii, 'b'); }
int test_ft_isdigit(void) { return run_char_test(ft_isdigit, isdigit, 'b'); }
int test_ft_isprint(void) { return run_char_test(ft_isprint, isprint, 'b'); }
int test_ft_tolower(void) { return run_char_test(ft_tolower, tolower, 'v'); }
int test_ft_toupper(void) { return run_char_test(ft_toupper, toupper, 'v'); }
