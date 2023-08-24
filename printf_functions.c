#include "main.h"

/************************* PRINTS A STRING *************************/
/**
 * print_string - function that prints a string
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  finds and calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (j = width - len; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - len; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/************************* PRINTS A CHAR*************************/
/**
 * print_char - Prints a character
 *
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  finds active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char b = va_arg(types, int);

	return (handle_write_char(b, buffer, flags, width, precision, size));
}

/************************* PRINTS AN INT*************************/
/**
 * print_int - function that prints an integer
 * @types: arguments
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned long int num;
	int is_negative = 0;
	int j = BUFF_SIZE - 2;
	long int n = va_arg(types, long int);

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/************************* PRINTS A PERCENT SIGN *************************/
/**
 * print_percent - function that prints a percent sign
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(precision);
	UNUSED(width);

	return (write(1, "%%", 1));
}

/************************* PRINTS AN UNSIGNED NUMBER *************************/
/**
 * print_binary -function that prints an unsigned number
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int cnt;
	unsigned int m, n, k, sum;
	unsigned int a[32];

	UNUSED(buffer);
	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;

	for (k = 1; k < 32; k++)
	{
		m /= 2;
		a[k] = (n / m) % 2;
	}
	for (k = 0, sum = 0, cnt = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			cnt++;
		}
	}
	return (cnt);
}
