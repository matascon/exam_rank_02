#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

static int	ft_nbrlen(long nbr, int len_base)
{
	int	len;

	len = 1;
	while (nbr >= len_base)
	{
		nbr /= len_base;
		len++;
	}
	return (len);
}

static void	ft_print_nbr(long nbr, int len_base, char *base)
{
	if (nbr >= len_base)
		ft_print_nbr(nbr / len_base, len_base, base);
	write(1, &base[nbr % len_base], 1);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	char	*fmt;
	char	*str;
	long	nbr;
	int		len;
	int		width;
	int		precision;
	int		negative;
	int		zeros;
	int		printed;

	va_start(args, format);
	fmt = (char *)format;
	printed = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			str = NULL;
			nbr = 0;
			width = 0;
			precision = -1;
			zeros = 0;
			len = 0;
			negative = 0;
			fmt++;
			while (*fmt >= '0' && *fmt <= '9')
			{
				width = (width * 10) + (*fmt - 48);
				fmt++;
			}
			if (*fmt == '.')
			{
				precision = 0;
				fmt++;
				while (*fmt >= '0' && *fmt <= '9')
				{
					precision = (precision * 10) + (*fmt - 48);
					fmt++;
				}
			}
			if (*fmt == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					str = "(null)";
				while (str[len])
					len++;
			}
			else if (*fmt == 'd')
			{
				nbr = va_arg(args, int);
				if (nbr < 0)
				{
					nbr *= -1;
					negative++;
				}
				len = ft_nbrlen(nbr, 10) + negative;
			}
			else if (*fmt == 'x')
			{
				nbr = va_arg(args, unsigned);
				len = ft_nbrlen(nbr, 16);
			}
			if (precision > len && *fmt != 's')
				zeros = precision - len + negative;
			else if (precision > -1 && precision < len && *fmt == 's')
				len = precision;
			else if (!precision && (*fmt == 's' || !nbr))
				len = 0;
			width = width - zeros - len;
			while (width-- > 0)
				printed += write(1, " ", 1);
			if (negative)
				write(1, "-", 1);
			while (zeros-- > 0)
				printed += write(1, "0", 1);
			if (*fmt == 's')
				printed += write(1, str, len);
			else if (len > 0 && (*fmt == 'd' || *fmt == 'x'))
			{
				if (*fmt == 'd')
					ft_print_nbr(nbr, 10, "0123456789");
				else
					ft_print_nbr(nbr, 16, "0123456789abcdef");
				printed += len;
			}
		}
		else
			printed += write(1, fmt, 1);
		fmt++;
	}
	va_end(args);
	return (printed);
}

int			main(void)
{
	int i;

	i = ft_printf("%10.2s\n", "toto");
	ft_printf("%d\n", i);
	i = ft_printf("Magic %s is %5d\n", "number", 42);
	ft_printf("%d\n", i);
	i = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("%d\n", i);
	ft_printf("\n********************************\n");
	i = ft_printf("<%5.d>\n", 0);
	ft_printf("%d\n", i);
	i = ft_printf("<%s>\n", NULL);
	ft_printf("%d\n", i);
	i = ft_printf("<%7.2s>\n", NULL);
	ft_printf("%d\n", i);
	i = ft_printf("<%7s>\n", NULL);
	ft_printf("%d\n", i);
	i = ft_printf("<%d>\n", 42);
	ft_printf("%d\n", i);
	i = ft_printf("<%10.5d>\n", -42);
	ft_printf("%d\n", i);
	i = ft_printf("<%15.10d>\n", INT_MIN);
	ft_printf("%d\n", i);
	i = ft_printf("<%15.10d>\n", INT_MAX);
	ft_printf("%d\n", i);
	i = ft_printf("<%15.11d>\n", INT_MAX);
	ft_printf("%d\n", i);
	i = ft_printf("<%15.11d>\n", INT_MIN);
	ft_printf("%d\n", i);
	i = printf("<%15.11d>\n", INT_MIN);
	ft_printf("%d\n", i);
	return (0);
}
