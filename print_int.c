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

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd' || *format == 'i')
			{
				int val;
				int div;
				val = va_arg(args, int);
				if (val < 0)
				{
					putchar('-');
					val = -val;
				}
				div = 1;
				while (val / div >= 10)
				{
					div *= 10;
				}
				while (div > 0)
				{
					int digt;
					digt = val / div;
					putchar(digt + '0');
					val %= div;
					div /= 10;
				}
			}
		}
		else
		{
			putchar(*format);
		}
		format++;
	}
	va_end(args);
}
/**
 * main - entry point for function.
 * Return: always 0
 */
int main(void)
{
	int n1 = 33;
	int n2 = -231;

	print_int("%d\n", n1);
	print_int("%i\n", n2);
	return (0);
}
