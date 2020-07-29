/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matascon <matascon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 08:29:10 by matascon          #+#    #+#             */
/*   Updated: 2020/07/13 11:10:35 by matascon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define F ft_printf
/*
static char	*ft_strdup(char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}*/

static char	*ft_base(long nbr, char *base)
{
	char	*str;
	long	nbr_copy;
	int		len_nbr;
	int		len_base;

	if (nbr < 0)
		nbr *= -1;
	nbr_copy = nbr;
	len_base = 0;
	while (base[len_base])
		len_base++;
	len_nbr = 0;
	while (nbr_copy >= 10)
	{
		nbr_copy /= len_base;
		len_nbr++;
	}
	len_nbr++;
	str = (char *)malloc(len_nbr + 1);
	if (!str)
		return (NULL);
	str[len_nbr--] = '\0';
	while (nbr >= 10)
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
	int		printed;
	int		len;
	int		i;
	int		j;

	fmt = (char *)format;
	printed = 0;
	i = 0;
	va_start(args, format);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			str = NULL;
			nbr = 0;
			width = 0;
			dot = 0;
			precision = 0;
			len = 0;
			j = 0;
			i++;
			while (fmt[i] >= '0' && fmt[i] <= '9')
				width = (width * 10) + fmt[i++] - 48;
			if (fmt[i] == '.')
			{
				dot = 1;
				i++;
				while (fmt[i] >= '0' && fmt[i] <= '9')
					precision = (precision * 10) + fmt[i++] - 48;
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
				if (len < precision || !dot)
					precision = len;
				width = width - precision;
				while (width-- > 0)
					printed += write(1, " ", 1);
				while (j < precision)
					printed += write(1, &str[j++], 1);
			}
			else if (fmt[i] == 'd' || fmt[i] == 'x')
			{
				if (nbr == 0 && dot && precision == 0)
				{
					while (width-- > 0)
						printed += write(1, " ", 1);
				}
				else
				{
					if (nbr < 0)
						width--;
					if (len <= precision)
						width -= precision;
					else
						width -= len;
					while (width-- > 0)
						printed += write(1, " ", 1);
					if (nbr < 0)
						printed += write(1, "-", 1);
					precision -= len;
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
		{
			write(1, &fmt[i], 1);
			printed++;
		}
		i++;
	}
	va_end(args);
	return (printed);
}
/*
int	main()
{
	int i;

	i = printf("Hola %7s %.3d %.0x %5.1d %.5s %d\n", "mateo", -42, 42, 0, NULL, INT_MAX + 1);
	ft_printf("%d\n", i);
	i = ft_printf("Hola %7s %.3d %.0x %5.1d %.5s %d\n", "mateo", -42, 42, 0, NULL, INT_MAX + 1);
	ft_printf("%d\n", i);
	ft_printf("%10.2s\n", "toto");
	ft_printf("Magic %s is %5d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("Simple test\n");
	ft_printf("");
	ft_printf("--Format---");
	F("\n");
	//ft_printf("%d", 0);
	F("%d", 1);
	F("\n");
	F("%d", 5454);
	F("\n");
	F("%d", (int)2147483647);
	F("\n");
	F("%d", (int)2147483648);
	F("\n");
	F("%d", (int)-2147483648);
	F("\n");
	F("%d", (int)-2147483649);
	F("\n");
	F("%x", 0);
	F("\n");
	F("%x", 42);
	F("\n");
	F("%x", 1);
	F("\n");
	F("%x", 5454);
	F("\n");
	F("%x", (int)2147483647);
	F("\n");
	F("%x", (int)2147483648);
	F("\n");
	F("%x", (int)-2147483648);
	F("\n");
	F("%x", (int)-2147483649);
	F("\n");
	F("%s", "");
	F("\n");
	F("%s", "toto");
	F("\n");
	F("%s", "wiurwuyrhwrywuier");
	F("\n");
	F("%s", NULL);
	F("\n");
	return (0);
}
*/