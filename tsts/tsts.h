/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tsts.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 09:58:49 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/29 15:34:07 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TSTS_H
# define TSTS_H

# include "libft.h"  // Test targets
# include <stdio.h>  // For printf() 
# include <ctype.h>  // For char system functions
# include <string.h> // For string system functions

typedef int (*t_test_fn)(void);      // int return: 0 = pass, 1 = fail
typedef int (*t_char_test_fn)(int);  // generalized test runner for Character classification functions

int	test_ft_isalnum(void);
int	test_ft_isalpha(void);
int	test_ft_isascii(void);
int	test_ft_isdigit(void);
int	test_ft_isprint(void);
int	test_ft_tolower(void);
int	test_ft_toupper(void);
int	test_ft_strlen(void);
int test_ft_strchr(void);
int test_ft_strrchr(void);

#endif