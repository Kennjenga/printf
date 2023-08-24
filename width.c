#include "main.h"

/**
 * get_width - Calculates the width
 *
 * @format: Formatted string
 * @i: the list of arguments to be printed.
 * @list: arguments list.
 *
 * Return: returns the width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int cur_j;
	int w = 0;

	for (cur_j = *i + 1; format[cur_j] != '\0'; cur_j++)
	{
		if (is_digit(format[cur_j]))
		{
			w *= 10;
			w += format[cur_j] - '0';
		}
		else if (format[cur_j] == '*')
		{
			cur_j++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = cur_j - 1;

	return (w);
}
