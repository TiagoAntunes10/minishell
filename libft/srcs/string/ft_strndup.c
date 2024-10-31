/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:24:11 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/30 19:27:46 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*res;
	size_t	len;

	len = ft_strlen(str);
	if (n < len)
		len = n;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, str, len);
	res[len] = '\0';
	return (res);
}
