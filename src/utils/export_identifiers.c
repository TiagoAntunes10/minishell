/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:49:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/23 21:36:47 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_valid_identifier(char *keyvalue)
{
	int	i;

	i = 0;
	if (!keyvalue || (!ft_isalpha(keyvalue[i]) && keyvalue[i] != '_'))
		return (0);
	while (keyvalue[++i] && keyvalue[i] != '=')
		if (!ft_isalnum(keyvalue[i])
			&& keyvalue[i] != '_' && keyvalue[i] != '=')
			return (0);
	i--;
	while (keyvalue[++i])
		if (!ft_isprint(keyvalue[i]))
			return (0);
	return (1);
}
