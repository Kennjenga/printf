#include "main.h"

/****************** PRINTS A POINTER ******************/
/**
 * print_pointer - function that prints the value of a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of printed chars.
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned long num_addrs;
	char extra_c = 0, padd = ' ';
	int indx = BUFF_SIZE - 2, len = 2, padd_start = 1;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(size);
	UNUSED(width);
	UNUSED(precision);

	if (addrs == NULL)
	{
		return (write(1, "(nil)", 5));
	}

	buffer[BUFF_SIZE - 1] = '\0';

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[indx--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padd = '0';
	}
	if (flags & F_PLUS)
	{
		extra_c = '+', len++;
	}
	else if (flags & F_SPACE)
		extra_c = ' ', len++;
	indx++;
	return (write_pointer(buffer, indx, len,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (str[k] != '\0')
	{
		if (is_printable(str[k]))
			buffer[k + offset] = str[k];
		else
			offset += append_hexa_code(str[k], buffer, k + offset);
		k++;
	}

	buffer[k + offset] = '\0';

	return (write(1, buffer, k + offset));
}

/****************** PRINTS A STRING IN REVERSE **********************/
/**
 * print_reverse - Prints reverse string.
 * @types: arguments
 * @buffer:a buffer array to handle print
 * @flags: gets active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of printed chars
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, cnt = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (k = 0; str[k]; k++)
		;

	for (k = k - 1; k >= 0; k--)
	{
		char s = str[k];

		write(1, &s, 1);
		cnt++;
	}
	return (cnt);
}
/************************* PRINTS A STRING IN ROT13 *************************/
/**
 * print_rot13string - function that print a string in rot13.
 * @types: a list of arguments
 * @buffer: a buffer array to handle print
 * @flags: active flags
 *  @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: returns the numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int cnt = 0;
	char s;
	char *str;
	unsigned int j, k;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);

	UNUSED(size);
	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(buffer);

	if (str == NULL)
	{
		str = "(AHYY)";
	}
	for (j = 0; str[j]; j++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[k])
			{
				s = out[k];
				write(1, &s, 1);
				cnt++;
				break;
			}
		}
		if (!in[k])
		{
			s = str[j];
			write(1, &s, 1);
			cnt++;
		}
	}
	return (cnt);
}
