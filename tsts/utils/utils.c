/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:49:59 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/09 21:51:38 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stddef.h>

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

char *glib__strjoin(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return NULL;

	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char *joined = malloc(len1 + len2 + 1);
	if (!joined)
		return NULL;

	memcpy(joined, s1, len1);
	memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	return joined;
}

char *ref__strtrim(const char *s1, const char *set)
{
	size_t start, end, len;
	char *out;

	if (!s1 || !set)
		return NULL;

	start = 0;
	while (s1[start] && strchr(set, s1[start]))
		start++;

	end = strlen(s1);
	while (end > start && strchr(set, s1[end - 1]))
		end--;

	len = end - start;
	out = malloc(len + 1);
	if (!out)
		return NULL;

	memcpy(out, s1 + start, len);
	out[len] = '\0';
	return out;
}

char **ref__split(const char *s, char delim)
{
	if (!s)
		return NULL;
	
	printf("\n**ref__split() called.\n");

	char **result = malloc(sizeof(char *) * 1024); // over-allocate defensively
	if (!result)
		return NULL;

	int i = 0;

	while (*s)
	{
		// Skip delimiters
		while (*s == delim)
			s++;

		if (!*s)
			break;

		const char *start = s;
		while (*s && *s != delim)
			s++;

		size_t len = s - start;
		result[i] = malloc(len + 1);
		if (!result[i])
		{
			// free all previously allocated strings
			for (int j = 0; j < i; j++)
				free(result[j]);
			free(result);
			return NULL;
		}
		memcpy(result[i], start, len);
		result[i][len] = '\0';
		i++;
	}

	result[i] = NULL;
	return result;
}