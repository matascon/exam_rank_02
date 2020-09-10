#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

static int	ft_nbrlen(long n, int base_len)
{
	int	i;

	i = 1;
	while (n >= base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

static void	ft_putnbr(long nbr, int base_len, char *base)
{
	if (nbr >= base_len)
		ft_putnbr(nbr / base_len, base_len, base);
	write(1, &base[nbr % base_len], 1);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	char	*str;
	char	*s;
	long	nbr;
	int		neg;
	int		len;
	int		width;
	int		prec;
	int		spaces;
	int		zeros;
	int		length;

	va_start(args, format);
	str = (char *)format;
	length = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			neg = 0;
			len = 0;
			width = 0;
			prec = -1;
			spaces = 0;
			zeros = 0;
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - 48);
				str++;
			}
			if (*str == '.')
			{
				prec = 0;
				str++;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + (*str - 48);
					str++;
				}
			}
			if (*str == 's')
			{
				s = va_arg(args, char *);
				if (!s)
					s = "(null)";
				while (s[len])
					len++;
			}
			if (*str == 'd')
			{
				nbr = va_arg(args, int);
				if (nbr < 0)
				{
					nbr = -nbr;
					neg = 1;
				}
				len = ft_nbrlen(nbr, 10) + neg;
			}
			if (*str == 'x')
			{
				nbr = va_arg(args, unsigned);
				len = ft_nbrlen(nbr, 16);
			}
			if (prec >= len && *str != 's')
				zeros = prec - len + neg;
			else if (prec > -1 && prec < len && *str == 's')
				len = prec;
			else if (prec == 0 && (*str == 's' || nbr == 0))
				len = 0;
			spaces = width - zeros - len;
			while (spaces-- > 0)
				length += write(1, " ", 1);
			if (neg == 1)
				write(1, "-", 1);
			while (zeros > 0)
			{
				length += write(1, "0", 1);
				zeros--;
			}
			if (*str == 's')
				write(1, s, len);
			else if (len > 0 && *str == 'd')
				ft_putnbr(nbr, 10, "0123456789");
			else if (len > 0 && *str == 'x')
				ft_putnbr(nbr, 16, "0123456789abcdef");
			length += len;
		}
		else
			length += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (length);
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
