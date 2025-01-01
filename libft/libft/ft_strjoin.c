/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:45:09 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/01 19:22:37 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_join(char const *s1, char const *s2, char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			j;
	char		*str;

	j = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(j + 1);
	str = ft_join(s1, s2, str);
	str[j] = '\0';
	return (str);
}

static char	*ft_join(char const *s1, char const *s2, char *str)
{
	int		i;

	i = 0;
	while (*s1 != '\0')
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	if (s2 == NULL)
		return (str);
	while (*s2 != '\0')
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	return (str);
}

/*
#include <stdio.h>

int main(int argc, char **argv)
{
	char	*str;

	if (argc != 3)
		return (0);
	str = ft_strjoin(argv[1], argv[2]);
	printf("%s\n", str);
}*/
