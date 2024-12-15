/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:58:12 by rapcampo          #+#    #+#             */
/*   Updated: 2023/10/27 12:58:21 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_nbr(int fd, size_t n, const char *base)
{
	int		count;
	size_t	base_len;

	count = 0;
	base_len = 0;
	if (base[0] == '-' && (ssize_t)n < 0)
	{
		n = (size_t)(-(ssize_t)n);
		count += write(fd, "-", 1);
		base++;
	}
	else if (base[0] == '-')
		base++;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
		count += ft_print_nbr(fd, n / base_len, base);
	count += write(fd, &base[n % base_len], 1);
	return (count);
}
