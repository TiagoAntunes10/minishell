/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:47:40 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/17 21:36:20 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(char const *str)
{
	int	l;

	if (str == NULL)
		return (0);
	l = 0;
	while (*str != '\0')
	{
		++l;
		++str;
	}
	return (l);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*str;

	str = "abcd";
	printf("%d\n", ft_strlen(str));
	printf("%ld\n", strlen(str));
}*/
