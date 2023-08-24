#include "main.h"

/**
 * get_size -Calculates the size to cast the argument
 * @format: Formatted string where to print the arguments
 * @i: arguments to be printed.
 *
 * Return: returns the precision.
 */
int get_size(const char *format, int *i)
{
	int cur_i = *i + 1;
	int size = 0;

	if (size == 0)
	{
		*i = cur_i - 1;
	}
	else
	{
		*i = cur_i;
	}
	if (format[cur_i] == 'l')
	{
		size = S_LONG;
	}
	else
	{
		if (format[cur_i] == 'h')
			size = S_SHORT;
	}
	return (size);
}
