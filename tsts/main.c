/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 16:07:29 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/04/27 15:29:34 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

int	main(void)
{
	//(void)tst_isalnum();
	run_char_test(ft_isalnum, isalnum, "isalnum");
}