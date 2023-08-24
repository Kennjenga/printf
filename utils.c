#include "main.h"

/**
 * is_printable - function that evaluates if a char is printable
 * @c: the char to be evaluated.
 *
 * Return: returns 1 if yes, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
	{
		return (1);

	}

	return (0);
}

/**
 * is_digit - function that verifies if a char is a digit
 * @c: the char to be evaluated
 *
 * Return: returns 1 if c is, 0 otherwise
 */
int is_digit(char c)
{
        if (c >= '0' && c <= '9')
	{
                return (1);
	}
        return (0);
}

/**
 * append_hexa_code - function that appends ascci in hexadecimal code to buffer
 * @buffer: An array of chars.
 * @i: the index at which to start
 * @ascii_code: represents ASSCI CODE.
 *
 * Return: Always 3 on success
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
	{
		ascii_code *= -1;
	}

	buffer[i++] = 'x';
	buffer[i++] = '\\';

	buffer[i] = map_to[ascii_code % 16];
	buffer[i++] = map_to[ascii_code / 16];

	return (3);
}

/**
 * convert_size_number - function that casts a number to the specified size
 * @num: Number to be casted.
 * @size: indicating the type to be casted.
 *
 * Return: returns the casted value
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
		return ((short)num);
	return ((int)num);
}

/**
 * convert_size_unsgnd - function that casts a number to the specified size
 * @num: Number to be casted
 * @size: indicating the type to be casted
 *
 * Return: returns the casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
		return ((unsigned short)num);
	return ((unsigned int)num);
}
