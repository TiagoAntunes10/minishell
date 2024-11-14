/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:14:30 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/30 19:17:18 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount_mult(char const *str, char const *delim)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		i += ft_strspn(&str[i], delim);
		if (str[i])
		{
			i += ft_strcspn(&str[i], delim);
			count++;
		}
	}
	return (count);
}
