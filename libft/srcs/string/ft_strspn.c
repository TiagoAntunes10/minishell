/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:59:58 by rapcampo          #+#    #+#             */
/*   Updated: 2024/03/29 18:02:01 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(char const *str, char const *accept)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(accept, str[i]))
		i++;
	return (i);
}
