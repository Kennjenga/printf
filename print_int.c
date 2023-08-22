#include "main.h"
#include <stdio.h>

/**
 * print_nums - function that prints an integer
 * @outp: the host output
 * @pos: the output position
 * @m: an int
 *
 * Return: returns an integer
 */
int print_nums(int m, char *outp, int pos)
{
	int x = 1, y = 0, z;

	if (m < 0)
	{
		outp[pos] = '-';
		pos++;
	}
	while (m / x > 9 || m / x < -9)
	{
		x = x * 10;
		y++;
	}
	for (z = 0; z <= y; z++)
	{
		if (m < 0)
			outp[pos] = (-(m / x) + '0');
		else
			outp[pos] = ((m / x) + '0');
		pos++;
		m = m % x;
		x = x / 10;
	}
	return (pos);
}
/**
 * print_int - functin that prints the specifier d
 * @l: the arguments passed to print
 * @outp: the host output
 * @pos: the output position
 *
 * Return: an int
 */
int print_int(va_list l, char *outp, int pos)
{
	return (print_nums(va_arg(l, int), outp, pos));
}
/**
 * print_single_int - prints the specifier i
 * @l: arguments passed to print
 * @outp: the host output
 * @pos: the output position
 *
 * Return: int
 */
int print_single_int(va_list l, char *outp, int pos)
{
	return (print_nums(va_arg(l, int), outp, pos));
}
