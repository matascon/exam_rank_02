#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

static char	*ft_base(long nbr, char *base)
{
	char	*str;
	long	copy;
	int		len_base;
	int		len_nbr;

	if (nbr < 0)
		nbr *= -1;
	len_base = 0;
	while (base[len_base])
		len_base++;
	len_nbr = 0;
	copy = nbr;
	while (copy >= len_base)
	{
		copy /= len_base;
		len_nbr++;
	}
	len_nbr++;
	str = (char *)malloc(len_nbr + 1);
	str[len_nbr--] = '\0';
	while (nbr >= len_base)
	{
		str[len_nbr--] = base[nbr % len_base];
		nbr /= len_base;
	}
	str[len_nbr] = base[nbr];
	return (str);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	char	*fmt;
	char	*str;
	long	nbr;
	int		width;
	int		dot;
	int		precision;
	int		i;
	int		j;
	int		len;
	int 	printed;

	fmt = (char *)format;
	i = 0;
	printed = 0;
	va_start(args, format);
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			str = NULL;
			width = 0;
			dot = 0;
			precision = 0;
			j = 0;
			len = 0;
			nbr = 0;
			i++;
			while (fmt[i] >= '0' && fmt[i] <= '9')
				width = width * 10 + (fmt[i++] - 48); 
			if (fmt[i] == '.')
			{
				dot = 1;
				i++;
				while (fmt[i] >= '0' && fmt[i] <= '9')
					precision = precision * 10 + (fmt[i++] - 48); 
			}
			if (fmt[i] == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					str = "(null)";
			}
			else if (fmt[i] == 'd')
			{
				nbr = (long)va_arg(args, int);
				str = ft_base(nbr, "0123456789");
			}
			else if (fmt[i] == 'x')
			{
				nbr = (long)va_arg(args, unsigned);
				str = ft_base(nbr, "0123456789abcdef");
			}
			while (str[len])
				len++;
			if (fmt[i] == 's')
			{
				if (len <= precision || !dot)
					precision = len;
				width -= precision;
				while (width-- > 0)
					printed += write(1, " ", 1);
				while (j < precision)
					printed += write(1, &str[j++], 1);
			}
			else if (fmt[i] == 'd' || fmt[i] == 'x')
			{
				if (!nbr && !precision && dot)
				{
					while (width-- > 0)
						printed += write(1, " ", 1);
				}
				else
				{
					if (nbr < 0)
						width--;
					if (precision < len)
						width -= len;
					else
						width -= precision;
					precision -= len;
					while (width-- > 0)
						printed += write(1, " ", 1);
					if (nbr < 0)
						printed += write(1, "-", 1);
					while (precision-- > 0)
						printed += write(1, "0", 1);
					while (j < len)
						printed += write(1, &str[j++], 1);
				}
				if (str)
					free(str);
			}
		}
		else
			printed += write(1, &fmt[i], 1);
		i++;
	}
	va_end(args);
	return (printed);
}

int main()
{
	int		i;
	int		j;
	i = printf("ft: jaja[%30.10s] [%.3s] [%.30s] [%20s] [%30.10d] [%30d %.10d] [%30.10d] [%5.0d] [%30.10x] [%30x] [%.10x] [%30.10x] [%5.0x]\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);
	printf("ft: %d\n", i);
	i = ft_printf("sy: jaja[%30.10s] [%.3s] [%.30s] [%20s] [%30.10d] [%30d %.10d] [%30.10d] [%5.0d] [%30.10x] [%30x] [%.10x] [%30.10x] [%5.0x]\n", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0);
	printf("sy: %d\n", i);
	i = printf("[%6d], [%10.3s]\n", -2147483648, "");
	printf("ft: %d\n", i);
	j = ft_printf("[%6d], [%10.3s]\n", -2147483648, "");
	printf("sy: %d\n", j);
	ft_printf("%x%x%x%x%x%x%x\n", 4242,4242,4242,4242,4242,4242,4242);
}
