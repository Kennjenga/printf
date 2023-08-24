#include "main.h"

/**
 * _printf - selects the correct function to print.
 * @format: identifier to check for
 * Return: string length
 */

int _printf(const char *format, ...)
{
	int j;
	int printd = 0, printd_chars = 0;
	int width, flags, precision, size, buff_indx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	{
		return (-1);
	}

	va_start(list, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			buffer[buff_indx++] = format[j];
			if (buff_indx == BUFF_SIZE)
			{
				print_buff(buffer, &buff_indx);
			}
			printd_chars++;
		}
		else
		{
			print_buff(buffer, &buff_indx);
			flags = get_flags(format, &j);
			width = get_width(format, &j, list);
			precision = get_precision(format, &j, list);
			size = get_size(format, &j);
			++j;
			printed = handle_print(format, &j, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buff(buffer, &buff_indx);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buff - Prints contents of the buff
 * @buffer: chars array
 * @buff_indx: index where to add next char
 */
void print_buff(char buffer[], int *buff_indx)
{
	if (*buff_indx > 0)
		write(1, &buffer[0], *buff_indx);

	*buff_indx = 0;
}
