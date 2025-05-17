/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:52:32 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/17 19:28:51 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

char	*glib__substr(const char *s, unsigned int start, size_t len);
char	*glib__strjoin(const char *s1, const char *s2);
char	*ref__strtrim(const char *s1, const char *set);
char	**ref__split(const char *s, char delim);

// ft_strmapi() test helper functions
char identity(unsigned int i, char c);
char uppercase_even(unsigned int i, char c);
char index_to_char(unsigned int i, char c);
char constant_Z(unsigned int i, char c);

// ft_striteri() testhelper functions:

void to_upper(unsigned int i, char *c);
void upper_even(unsigned int i, char *c);
void add_index_to_char(unsigned int i, char *c);
void noop(unsigned int i, char *c);

#endif
