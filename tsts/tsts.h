/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tsts.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 09:58:49 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/27 17:53:15 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TSTS_H
# define TSTS_H

# include "libft.h"
# include <stdio.h>
# include <ctype.h>

typedef int (*char_test_fn)(int);
int	run_char_test(char_test_fn ft_func, char_test_fn sys_func, const char *name)

#endif