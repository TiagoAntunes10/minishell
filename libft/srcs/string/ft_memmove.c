/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:07:33 by rapcampo          #+#    #+#             */
/*   Updated: 2023/10/12 17:20:05 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*d;

	d = s1;
	if (d < (unsigned char *)s2)
		return (ft_memcpy(s1, s2, n));
	else if (d > (unsigned char *)s2)
		while (n--)
			d[n] = ((unsigned char *)s2)[n];
	return (s1);
}
