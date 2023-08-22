#include <stdarg.h>
#include <stdio.h>

/**
 * print_int - handles the %d and %i conversion specifiers.
 * @format: character sequence that defines how
 * the output should be formatted.
 */
void print_int(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	int val, div;
	int digt;

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd' || *format == 'i')
			{
				val = va_arg(args, int);
				if (val < 0)
				{
					_putchar('-');
					val = -val;
				}
				div = 1;
				while (val / div >= 10)
				{
					div *= 10;
				}
				while (div > 0)
				{
					digt = val / div;
					_putchar(digt + '0');
					val %= div;
					div /= 10;
				}
			}
		}
		else
		{
			_putchar(*format);
		}
		format++;
	}
	va_end(args);
}
