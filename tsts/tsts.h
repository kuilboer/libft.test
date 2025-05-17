/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tsts.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/27 09:58:49 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/17 13:24:05 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TSTS_H
# define TSTS_H

# include "libft.h"  // Test targets
# include <stdio.h>  // For printf() 
# include <ctype.h>  // For char system functions
# include <string.h> // For string system functions
# include <bsd/string.h> // For string system functions from libbsd
# include <stdlib.h>
# include <limits.h> // for use of INT_MAX and INT_MIN

typedef int (*t_test_fn)(void);      // int return: 0 = pass, 1 = fail
typedef int (*t_char_test_fn)(int);  // generalized test runner for Character classification functions

int	test_ft_isalnum(void);
int	test_ft_isalpha(void);
int	test_ft_isascii(void);
int	test_ft_isdigit(void);
int	test_ft_isprint(void);
int	test_ft_tolower(void);
int	test_ft_toupper(void);
int test_ft_atoi(void);
int test_ft_strdup(void);
int	test_ft_strlen(void);
int test_ft_strchr(void);
int test_ft_strrchr(void);
int test_ft_strncmp(void);
int test_ft_strnstr(void);
int test_ft_strlcat(void);
int test_ft_strlcpy(void);
int test_ft_bzero(void);
int	test_ft_calloc(void);
int test_ft_memcmp(void);
int test_ft_memcpy(void);
int test_ft_memmove(void);
int test_ft_memset(void);
int test_ft_substr(void);
int test_ft_strjoin(void);
int test_ft_strtrim(void);
int test_ft_split(void);
int	test_ft_itoa(void);

#endif