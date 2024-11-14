/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:23:19 by rapcampo          #+#    #+#             */
/*   Updated: 2023/10/27 12:58:50 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_string(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		count += 6;
		return (count);
	}
	while (*str)
	{
		count += ft_char((int) *str);
		++str;
	}
	return (count);
}

int	ft_pointer(size_t ptr, const char *base)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_print_nbr(1, ptr, base);
	return (count);
}

int	print_format(char function, va_list ap)
{
	int	count;

	count = 0;
	if (function == 'c')
		count += ft_char(va_arg(ap, int));
	else if (function == 's')
		count += ft_string(va_arg(ap, char *));
	else if (function == 'd' || function == 'i')
		count += ft_print_nbr(1, va_arg(ap, int), SDECIMAL);
	else if (function == 'x')
		count += ft_print_nbr(1, va_arg(ap, unsigned int), HEX_LO);
	else if (function == 'X')
		count += ft_print_nbr(1, va_arg(ap, unsigned int), HEX_UP);
	else if (function == 'u')
		count += ft_print_nbr(1, va_arg(ap, unsigned int), UDECIMAL);
	else if (function == 'p')
		count += ft_pointer(va_arg(ap, size_t), HEX_LO);
	else
		count += write(1, &function, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}
