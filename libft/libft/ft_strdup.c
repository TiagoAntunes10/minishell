/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 09:07:16 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/27 14:18:55 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*char	*ft_strdup(char const *src)
{
	unsigned int		l;
	char				*str;

	l = ft_strlen(src);
	str = malloc (l);
	ft_strlcpy(str, src, l + 1);
	return (str);
}*/

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	i = 0;
	while (s[i])
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return ((void *) 0);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char	*src;

	src = "Boas dfjb fhbb";
	printf("ft_strdup: %s\n", ft_strdup(src));
	printf("strdup: %s\n", strdup(src));
}*/
