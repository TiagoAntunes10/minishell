/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:48:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/21 15:35:39 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	len;

	len = 0;
	while (str[len] && !ft_strchr(reject, str[len]))
		len++;
	return (len);
}
