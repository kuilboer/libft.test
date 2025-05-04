/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_mem.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/04 19:39:40 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_memset_test(void *sys_s, void *ft_s, int c, size_t n)
{
	void *expected = memset(sys_s, c, n);
	void *actual = ft_memset(ft_s, c, n);

	if (memcmp(expected, actual, n) != 0)
	{
		// printf("FAIL: memcmp(expected, actual, %zu) != 0", n);
		
		printf("FAIL: memcmp failed for c = 0x%02X, n = %zu\n", c, n);
		for (size_t j = 0; j < n; j++)
		{
			printf("Byte %zu: expected = %02X, actual = %02X\n", 
				j, ((unsigned char *)expected)[j], ((unsigned char *)actual)[j]);
		}
		return (1); //FAIL
	}
	return (0); //PASS
}



int test_ft_memset(void)
{
	int		i = 0;
	unsigned char	c[] = {0XAA, 0XFF, 0X00, 0xDE, 0xAD, 0xBE, 0xEF, '\0'};
	size_t			n[] = { 0, 1, 10, 60};
	unsigned char	sys_s[50];
	unsigned char	ft_s[50];

	memset(sys_s, 0X00, 50);
	memset(ft_s, 0X00, 50);
	i = 0;
    while (c[i] != '\0')
    {
		memset(sys_s, 0X00, 50);
		memset(ft_s, 0X00, 50);
		int ni = (sizeof(n)/sizeof(n[0]))-1;
		while (ni > 0)
		{
			if (run_memset_test(sys_s, ft_s, c[i], n[ni]))
				return (1); // fail
			ni--;
		}
		i++;
    }
    return (0); // pass
}

