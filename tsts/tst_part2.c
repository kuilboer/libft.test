/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tst_part2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: okuilboe <okuilboe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:27:39 by okuilboe      #+#    #+#                 */
/*   Updated: 2025/05/07 19:58:00 by okuilboe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include "tsts.h"

// Trusted reference function (from GLib or your own implementation)
//char *glib__substr(const char *s, unsigned int start, size_t len);  // assume this exists

static int run_substr_test(const char *input, unsigned int start, size_t len)
{
	char *expected = glib__substr(input, start, len);  // trusted
	char *actual = ft_substr(input, start, len);       // your implementation
	int failed = 0;

	if ((expected == NULL && actual != NULL) ||
		(expected != NULL && actual == NULL) ||
		(expected && actual && strcmp(expected, actual) != 0))
	{
		printf("FAIL: ft_substr(\"%s\", %u, %zu)\n", input, start, len);
		printf("   expected: \"%s\"\n", expected ? expected : "NULL");
		printf("   got     : \"%s\"\n", actual ? actual : "NULL");
		failed = 1;
	}
	free(expected);
	free(actual);
	return failed;
}

int test_ft_substr(void)
{
	const char *inputs[] = {
		"Hello World",
		"Hello World",
		"Hello World",
		"Hello",
		"Hello",
		"Hello",
		NULL
	};
	unsigned int starts[] = {0, 6, 6, 10, 0, 2};
	size_t lens[]         = {5, 5, 100, 5, 0, 1};

	int i = 0;
	while (inputs[i])
	{
		if (run_substr_test(inputs[i], starts[i], lens[i]))
			return 1; // fail
		i++;
	}
	if (run_substr_test(NULL, 0, 5)) // NULL input
		return 1;

	if (run_substr_test("Ends here", strlen("Ends here"), 5)) // start == strlen
		return 1;

	if (run_substr_test("€uro", 0, 1)) // UTF-8 start
		return 1;

	if (run_substr_test("  hello  ", 2, 5)) // trimming test
		return 1;

	return 0; // all passed
}