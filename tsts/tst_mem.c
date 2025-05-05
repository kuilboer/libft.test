/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_mem.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/05 13:29:07 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_memcpy_test(const void *src_data, size_t len, size_t n)
{
	/* create sys_d and ft_d buffers for comparison with a length of (size_t)len */
	unsigned char	*src = (unsigned char *)src_data;
	unsigned char	*dst_sys = calloc(1, len);
	unsigned char	*dst_ft = calloc(1, len);
	if (!dst_sys || !dst_ft)
		return (-1);

	void	*ret_sys = memcpy(dst_sys, src, n);
	void	*ret_ft = ft_memcpy(dst_ft, src, n);

	if (memcmp(ret_ft, ret_sys, n) != 0 || ret_ft != dst_ft)
	{
		for (size_t i = 0; i < len; i++)
		{
			printf("Byte %02zu: std = %02X, ft = %02X\n", i, dst_sys[i], dst_ft[i]);
		}
		free(dst_sys);
		free(dst_ft);
		return (1); //FAIL
	}
	free(dst_sys);
	free(dst_ft);
	return (0); //PASS
}

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

int test_ft_memcpy(void)
{
	unsigned char src_data[32];
	for (size_t i = 0; i < sizeof(src_data); i++)
		src_data[i] = (unsigned char)(i + 1);  // Fill with 0x01, 0x02, ..., 0x20

	int fails = 0;

	// Test various lengths
	size_t test_sizes[] = {0, 1, 5, 16, 31, 32};
	size_t num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);

		for (size_t i = 0; i < num_sizes; i++)
	{
		if (run_memcpy_test(src_data, sizeof(src_data), test_sizes[i]) != 0)
			fails++;
	}

	if (fails != 0)
		return (1);
	return (0); // pass
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

