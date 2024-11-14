/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:34:59 by rapcampo          #+#    #+#             */
/*   Updated: 2023/11/03 12:35:06 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	ft_get_strlen(char *str)
{
	size_t	i;

	i = (size_t)-1;
	while (str[++i])
		;
	return (i);
}

char	*ft_get_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

void	*ft_get_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = (size_t)-1;
	ptr = (void *)malloc(nmemb * size);
	if (ptr)
	{
		while (++i < nmemb * size)
			*((unsigned char *)ptr + i) = 0;
	}
	return (ptr);
}

void	fill_buffer(char *str)
{
	char	*has_nl;
	size_t	i;
	size_t	len;

	has_nl = ft_get_strchr(str, '\n');
	i = 0;
	if (has_nl)
	{
		len = ft_get_strlen(has_nl + 1);
		while (i < len)
		{
			str[i] = has_nl[i + 1];
			i++;
		}
		while (i < BUFFER_SIZE)
			str[i++] = '\0';
	}
	else
	{
		while (i < BUFFER_SIZE)
			str[i++] = 0;
	}
}

char	*ft_get_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = (size_t)-1;
	j = (size_t)-1;
	if (!s1)
		s1 = (char *)ft_get_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	res = ft_get_calloc(ft_get_strlen(s1)
			+ ft_get_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j] && s2[j] != '\n')
		res[i++] = s2[j];
	res[i] = s2[j];
	if (s2[j] == '\n')
		res[++i] = '\0';
	fill_buffer(s2);
	free(s1);
	return (res);
}
