/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_test_helpers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/17 17:30:41 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/17 19:31:24 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Helper functions for testing ft_strmapi():

char identity(unsigned int i, char c)
{
	(void)i;
	return c;
}

char uppercase_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return c - 32;
	return c;
}

char index_to_char(unsigned int i, char c)
{
	(void)c;
	return '0' + (i % 10);
}

char constant_Z(unsigned int i, char c)
{
	(void)i;
	(void)c;
	return 'Z';
}

// Helper functions for testing ft_striteri():

void to_upper(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

void upper_even(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c -= 32;
}

void add_index_to_char(unsigned int i, char *c)
{
	*c += i;
}

void noop(unsigned int i, char *c)
{
	(void)i;
	(void)c;
}