/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:49:59 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/07 18:52:21 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
This is a reference implementation of glib_substr it is used to provide base-
line value for some of the libft functions.
*/
char *glib__substr(const char *s, unsigned int start, size_t len)
{
	if (!s)
		return NULL;

	size_t slen = strlen(s);
	if (start >= slen)
		return strdup("");  // Return empty string if start is beyond end

	size_t maxlen = slen - start;
	size_t actual_len = len < maxlen ? len : maxlen;

	char *substr = malloc(actual_len + 1);
	if (!substr)
		return NULL;

	memcpy(substr, s + start, actual_len);
	substr[actual_len] = '\0';
	return substr;
}