#include "main.h"

/**
 * get_flags - Calculates active flags
 *
 * @format: formatted string in which to print the arguments
 * @i: a parameter
 * Return: returns flags
 */
int get_flags(const char *format, int *i)
{

	int flags = 0;
	int k;
	int curr_i;

	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (k = 0; FLAGS_CH[k] != '\0'; k++)
			if (format[curr_i] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}

		if (FLAGS_CH[k] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
