/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:32:00 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/30 17:34:10 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(char const *str, char const *accept)
{
	char const *res;

	res = str + ft_strcspn(str, accept);
	if (!*res)
		return (NULL);
	return ((char *)res);
}
