/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:14:16 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/30 17:15:45 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stpcpy(char *restrict dst, const char *restrict src)
{
	char *p;
	
	return (p = ft_mempcpy(dst, src, ft_strlen(src)), *p = 0, p);
}
