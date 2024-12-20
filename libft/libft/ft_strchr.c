/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:39:23 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/17 18:57:53 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strchr(char const *s, int c)
{
	char	*cs;

	cs = (char *) s;
	while (*cs != '\0')
	{
		if (*cs == c)
			return (cs);
		else
			cs++;
	}
	if (*cs == c)
		return (cs);
	else
		return ("\0");
}*/

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char    *s;
    char    c;

    s = "hfdb hnjnhdfb";
    c = 'n';
    printf("ft_strchr: %s\n", ft_strchr(s, c));
    printf("strchr: %s\n", strchr(s, c));
}*/
