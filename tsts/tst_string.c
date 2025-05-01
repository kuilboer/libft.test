/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_string.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 15:35:57 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/01 21:36:25 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tsts.h"

static int run_strlen_test(const char *s)
{
	//return (ft_strlen(s) != strlen(s));
	size_t expected = strlen(s);
    size_t actual = ft_strlen(s);

    if (expected != actual)
    {
        printf("FAIL: strlen(\"%s\") expected %zu, got %zu\n", s, expected, actual);
        return (1);
    }
    return (0);
}

static int run_strchr_test(const char *s, int c)
{
	char *expected = strchr(s, c);
	char *actual = ft_strchr(s, c);
	
	if (actual != expected)
	{
		printf("FAIL: strchr(\"%s\", \"%c\") expected %s(%p), got %s(%p)\n", s, c, expected, expected, actual, actual);
		return (1); // false
	}
	return (0);
}

static int run_strrchr_test(const char *s, int c)
{
	char *expected = strrchr(s, c);
	char *actual = ft_strrchr(s, c);
	
	if (actual != expected)
	{
		printf("FAIL: strchr(\"%s\", \"%c\") expected %s(%p), got %s(%p)\n", s, c, expected, expected, actual, actual);
		return (1); // false
	}
	return (0);
}

static int run_strncmp_test(const char *s1, const char *s2, size_t n)
{
	int expected =  strncmp(s1, s2, n);
	int actual = ft_strncmp(s1, s2, n);
	
	if (actual != expected)
	{
		printf("FAIL: strncmp(\"%s\", \"%s\", %zu) expected %d, got %d\n", s1 ,s2 , n, expected, actual);
		return (1); // false
	}
	return (0);
}

static int run_strnstr_test(const char *haystack, const char *needle, size_t len)
{
	char	*expected =  strnstr(haystack, needle, len);
	char	*actual = ft_strnstr(haystack, needle, len);
	
	if ((expected == NULL && actual != NULL) || \
		(expected != NULL && actual == NULL) || \
		(expected && actual && strcmp(expected, actual) != 0))
	{
		printf("FAIL: strnstr(\"%s\", \"%s\", %zu) expected %s, got %s\n", haystack ,needle , len, expected, actual);
		return (1); // false
	}
	return (0);
}

static int run_strlcat_test(char *dst_ft, char *dst, const char *src, size_t size)
{
	// for strlcat it is not enough to compare the return values only because
	// that only reproduces the original length of the src string.
	// so we need to destination buffers for each individual function to compare
	// the results of the actual copy.

	size_t	expected =  strlcat(dst, src, size);
	size_t	actual = ft_strlcat(dst_ft, src, size);
	
	if (actual != expected || strcmp(dst_ft, dst) != 0)
	{
		printf("FAIL: strlcat(\"%s\", \"%s\", %zu) expected %s - (%zu), got %s - (%zu)\n", dst ,src , size, dst, expected, dst_ft, actual);
		return (1); // false
	}
	return (0);
}

static int run_strlcpy_test(char *dst_ft, char *dst, const char *src, size_t size)
{
	// for strlcpy it is not enough to compare the return values only because
	// that only reproduces the original length of the src string.
	// so we need to destination buffers for each individual function to compare
	// the results of the actual copy.

	size_t	expected =  strlcpy(dst, src, size);
	size_t	actual = ft_strlcpy(dst_ft, src, size);
	
	if (actual != expected || strcmp(dst_ft, dst) != 0)
	{
		printf("FAIL: strlcpy(\"%s\", \"%s\", %zu) expected %s - (%zu), got %s - (%zu)\n", dst ,src , size, dst, expected, dst_ft, actual);
		return (1); // false
	}
	return (0);
}

int test_ft_strlen(void)
{
	int			i = 0;
	const char	*tests[] = {"", "abc", "42 network", "\n", " ", 0};
	const char  arr[] = {'H', 'e', '\0', 'l', 'l','o'};

	i = 0;
    while (tests[i])
    {
        if (run_strlen_test(tests[i]))
            return (1); // fail
        i++;
    }
	if (run_strlen_test(arr + 2))
            return (1); // fail
    return (0); // pass
}

int test_ft_strchr(void)
{
	int i;
	const char *str[] = {"Hello", "Network42", "not_found", "First_char", "last_chaR",0};
	const char c[] = {'l', '4', '-', 'F', 'R'};

	i = 0;
	while (str[i])
	{
		if (run_strchr_test(str[i], c[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}

int test_ft_strrchr(void)
{
	int i;
	const char *str[] = {"Hello", "Network42", "not_found", "First_char", "last_chaR", "", "Find the termination character",0};
	const char c[] = {'l', '4', '-', 'F', 'R', 'a', '\0'};

	i = 0;
	while (str[i])
	{
		if (run_strrchr_test(str[i], c[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}

int test_ft_strncmp(void)
{
	int i;
	const char *str1[] = {"ABC", "ABC", "ABB", "S1_is_longer", "S1_is_shorter", "", "", "S2_is_empty", "HelloWorld",NULL};
	const char *str2[] = {"ABC", "ABB", "ABC", "S1", "S1_is_shorter_than_S2__", "", "S1_is_empty", "", "HelloApple",NULL};
	size_t count[] = {3, 3, 3, 3, 15, 15, 3, 3, 5};

	i = 0;
	while (str1[i] && str2[i] && count[i])
	{
		if (run_strncmp_test(str1[i], str2[i], count[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}

int test_ft_strnstr(void)
{
	int i;
	const char *haystack[] = {"String match start", \
								"String match middle", \
								"Multiple matches Multi", \
								"Empty needle.", \
								"To short len for match", \
								"tiny haystack abc", \
								"", \
								NULL};
	const char *needle[]   = {"String", \
								"match", \
								"Multi", \
								"", \
								"len", \
								"Super large needle abcd", \
								"", \
								NULL};
	size_t count[]         = {6, 12, 22, 25, 25, 10, 0};

	i = 0;
	while (haystack[i] && needle[i] && count[i])
	{
		if (run_strnstr_test(haystack[i], needle[i], count[i]))
			return (1); // fail
		i++;
	}
	return (0); // pass
}

int test_ft_strlcat(void)
{
	size_t		i;
	int 		result;
	size_t		elements;
	char		*dst_vals[] = {"0123456", "6543210",   "",   "", NULL};
	char		*dst1[5];
	char		*dst2[5];
	const char	*src[] = {   "aaaa", "999999999", "", "\0", NULL};

	i = 0;
	// In order to have changable Array with varying element sizes we need to
	// alocate memory for the individual elements;
	while (dst_vals[i])
	{
		dst1[i] = malloc(ft_strlen(dst_vals[i]) + 10);
		dst2[i] = malloc(ft_strlen(dst_vals[i]) + 10);
		if (!dst1[i] || !dst2[i]){printf("\ntest_ft_strlcpy: Memory allocation failed!\n"); return(1);}
		strcpy(dst1[i], dst_vals[i]);
		strcpy(dst2[i], dst_vals[i]);
		i++;
	}
	dst1[i] = NULL;
	dst2[i] = NULL;
	elements = i;

	result = 0;
	i = 0;
	while (dst1[i] && dst2[i] && src[i])
	{
		if (run_strlcat_test(dst1[i], dst2[i], src[i], ft_strlen(dst1[i])) ||
			run_strlcat_test(dst1[0], dst2[0], src[0], 0) ||	// Edge case where nothing is wrten to dst only strlen(src) is returned.
			run_strlcat_test(dst1[0], dst2[0], src[0], 1))		// Edge case where only '\0' is written to dst turning its value to "".
		{
			result = 1;
			break;
			//return (1); // fail
		}
		i++;
	}

	while (elements > 0)
	{
		elements--;
		free(dst1[elements]);
		free(dst2[elements]);
	}
	
	return (result); // pass
}

int test_ft_strlcpy(void)
{
	size_t		i;
	int 		result;
	size_t		elements;
	char		*dst_vals[] = {"0123456", "6543210",   "",   "", NULL};
	char		*dst1[5];
	char		*dst2[5];
	const char	*src[] = {   "aaaa", "999999999", "", "\0", NULL};

	i = 0;
	// In order to have changable Array with varying element sizes we need to
	// alocate memory for the individual elements;
	while (dst_vals[i])
	{
		dst1[i] = malloc(strlen(dst_vals[i]) + 1);
		dst2[i] = malloc(strlen(dst_vals[i]) + 1);
		if (!dst1[i] || !dst2[i]){printf("\ntest_ft_strlcpy: Memory allocation failed!\n"); return(1);}
		strcpy(dst1[i], dst_vals[i]);
		strcpy(dst2[i], dst_vals[i]);
		i++;
	}
	dst1[i] = NULL;
	dst2[i] = NULL;
	elements = i;

	result = 0;
	i = 0;
	while (dst1[i] && dst2[i] && src[i])
	{
		if (run_strlcpy_test(dst1[i], dst2[i], src[i], strlen(dst1[i])) ||
			run_strlcpy_test(dst1[0], dst2[0], src[0], 0) ||	// Edge case where nothing is wrten to dst only strlen(src) is returned.
			run_strlcpy_test(dst1[0], dst2[0], src[0], 1))		// Edge case where only '\0' is written to dst turning its value to "".
		{
			result = 1;
			break;
			//return (1); // fail
		}
		i++;
	}

	while (elements > 0)
	{
		elements--;
		free(dst1[elements]);
		free(dst2[elements]);
	}
	
	return (result); // pass
}