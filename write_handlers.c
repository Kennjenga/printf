#include "main.h"

/************************* HANDLE WRITE*************************/
/**
 * handle_write_char - function that prints a string
 * @c: char type
 * @buffer: array
 * @flags: active flags.
 * @width: width.
 * @precision: precision specifier
 * @size: Size spe
 *
 * Return: Number of printed chars
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	char padd = ' ';
	int k = 0;

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
	{
		padd = '0';
	}

	buffer[k++] = c;
	buffer[k] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
		{
			buffer[BUFF_SIZE - k - 2] = padd;
		}

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
		}
	}
	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - function that prints a string
 * @is_negative: arguments
 * @ind: character type.
 * @buffer: array to handle print
 * @flags: active flags
 * @width: the width.
 * @precision: precision
 * @size: Size
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	char padd = ' ';
	char extra_ch = 0;
	int len = BUFF_SIZE - ind - 1;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padd = '0';
	}
	if (is_negative)
	{
		extra_ch = '-';
	}
	else if (flags & F_PLUS)
	{
		extra_ch = '+';
	}
	else if (flags & F_SPACE)
	{
		extra_ch = ' ';
	}

	return (write_num(ind, buffer, flags, width, precision,
		len, padd, extra_ch));
}

/**
 * write_num - function to write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision
 * @length: Number len
 * @padd: Pading character
 * @extra_c: Extra character
 *
 * Return: returns the number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int j, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
			buffer[j] = padd;
		buffer[j] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - function that writes an unsigned number
 * @is_negative: Number indicating if num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags
 * @width: Width
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: returns number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	char padd = ' ';
	int i = 0;
	int len = BUFF_SIZE - ind - 1;

	UNUSED(size);
	UNUSED(is_negative);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	{
		return (0);
	}

	if (precision > 0 && precision < len)
	{
		padd = ' ';
	}

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
		else
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
	}
	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - function that writes a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width
 * @flags: Flags
 * @padd: Character representing the padding
 * @extra_c: Character representing extra char
 * @padd_start: Index for padding to start
 *
 * Return: returns the number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int l;

	if (width > length)
	{
		for (l = 3; l < width - length + 3; l++)
			buffer[l] = padd;
		buffer[l] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';

			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], l - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], l - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], l - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
