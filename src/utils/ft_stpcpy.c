/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:21:11 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/26 18:03:26 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	*ft_mempcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (NULL);
	while (n--)
		*(char *)dest++ = *(char *)src++;
	return (dest);
}

char	*ft_stpcpy(char *restrict dst, char const *restrict src)
{
	char	*ptr;

	ptr = ft_mempcpy(dst, src, ft_strlen(src));
	*ptr = 0;
	return (ptr);
}
