#include "main.h"

/************************* PRINTS AN UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @types: arguments
 * @buffer: Buffer array
 * @flags:  gets active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[j--] = '0';
	}

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/************** PRINTS AN UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: arguments
 * @buffer: a buffer array to handle print
 * @flags: gets active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_hexadecimal(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        return (print_hexa(types, "0123456789abcdef", buffer,
                flags, 'x', width, precision, size));
}

/************* UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - function that prints an unsigned number in octal notation
 * @types: arguments
 * @buffer: Buffer array
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of printed chars
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[k--] = '0';

	k++;

	return (write_unsgnd(0, k, buffer, flags, width, precision, size));
}

/*************UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: arguments
 * @buffer: a buffer array to handle print
 * @flags: gets active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** HEXA NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 *
 * @types: List of arguments
 * @map_to: Array of values to map to
 * @buffer: a buffer array to handle print
 * @flags: gets active flags
 * @flag_ch: gets active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[k--] = '0';
	}

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[k--] = flag_ch;
		buffer[k--] = '0';
	}

	k++;

	return (write_unsgnd(0, k, buffer, flags, width, precision, size));
}
