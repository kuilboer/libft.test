/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_mem.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/05 15:49:25 by okuilboe      ########   odam.nl         */
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

static int run_memmove_test(unsigned char *src_data, size_t len, size_t offset, size_t n, int reverse)
{
	// Allocate extra space for offset movement
	unsigned char *sys_buf = calloc(1, len + offset);
	unsigned char *ft_buf  = calloc(1, len + offset);
	if (!sys_buf || !ft_buf)
		return (-1);

	// Initialize both buffers with src_data
	memcpy(sys_buf, src_data, len);
	memcpy(ft_buf, src_data, len);

	// Determine source and destination pointers
	unsigned char *sys_src, *sys_dst;
	unsigned char *ft_src, *ft_dst;

	if (!reverse)
	{
		sys_src = sys_buf;
		sys_dst = sys_buf + offset;

		ft_src = ft_buf;
		ft_dst = ft_buf + offset;
	}
	else
	{
		sys_src = sys_buf + offset;
		sys_dst = sys_buf;

		ft_src = ft_buf + offset;
		ft_dst = ft_buf;
	}

	void *ret_sys = memmove(sys_dst, sys_src, n);
	void *ret_ft  = ft_memmove(ft_dst, ft_src, n);

	// Compare the entire region
	if (memcmp(sys_buf, ft_buf, len + offset) != 0 || ret_sys != sys_dst || ret_ft != ft_dst)
	{
		printf("Failed at offset = %zu, n = %zu, reverse = %d\n", offset, n, reverse);
		for (size_t i = 0; i < len + offset; i++)
			printf("Byte %02zu: std = %02X, ft = %02X\n", i, sys_buf[i], ft_buf[i]);

		free(sys_buf);
		free(ft_buf);
		return (1);
	}

	free(sys_buf);
	free(ft_buf);
	return (0);
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

int test_ft_memmove(void)
{
	unsigned char src_data[64];
	for (size_t i = 0; i < sizeof(src_data); i++)
		src_data[i] = (unsigned char)(i + 1);

	int fails = 0;

	struct {
		size_t offset;
		size_t n;
	} tests[] = {
		{0, 0},      // No-op
		{0, 1},      // Single byte
		{2, 10},     // Forward overlap
		{10, 10},    // Backward overlap
		{5, 20},     // Medium backward
		{16, 32},    // Large backward (more than half)
		{32, 32},    // Full buffer backward
		{4, 64},     // Full buffer with large n
		{0, 100},    // Overrun beyond len (invalid, expect test to skip)
	};

	// for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
	// {
	// 	if (run_memmove_test(src_data, 32, tests[i].offset, tests[i].n, 0)) // forward
	// 		fails++;
	// 	if (run_memmove_test(src_data, 32, tests[i].offset, tests[i].n, 1)) // backward
	// 		fails++;
	// }

	for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
	{
		if (tests[i].n > 32 + tests[i].offset)
		{
			//printf("Skipping test: offset=%zu, n=%zu (out of bounds)\n", tests[i].offset, tests[i].n);
			continue;
		}
		if (run_memmove_test(src_data, 32, tests[i].offset, tests[i].n, 0)) // forward
			fails++;
		if (run_memmove_test(src_data, 32, tests[i].offset, tests[i].n, 1)) // backward
			fails++;
	}


	return (fails == 0 ? 0 : 1);
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

