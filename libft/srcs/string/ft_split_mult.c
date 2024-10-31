/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:04:41 by rapcampo          #+#    #+#             */
/*   Updated: 2024/04/06 21:25:10 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_mult(char const *str, char const *delim)
{
	char		**res;
	char const	*tok;
	int			i;

	res = ft_calloc(sizeof(char *), ft_wordcount_mult(str, delim) + 1);
	if (!res)
		return (free(res), NULL);
	tok = str + ft_strspn(str, delim);
	str = tok + ft_strcspn(tok, delim);
	i = -1;
	while (*tok)
	{
		res[++i] = ft_strndup(tok, str - tok);
		if (!res[i])
			return (ft_freematrix(res));
		tok = str + ft_strspn(str, delim);
		str = tok + ft_strcspn(tok, delim);
	}
	res[++i] = NULL;
	return (res);
}
