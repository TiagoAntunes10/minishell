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
	{
		if (keyvalue[i] == '+' && keyvalue[i + 1] == '=')
		{
			i++;
			break ;
		}
		else if (!ft_isalnum(keyvalue[i])
			&& keyvalue[i] != '_' && keyvalue[i] != '=')
			return (0);
	}
	i--;
	while (keyvalue[++i])
		if (!ft_isprint(keyvalue[i]))
			return (0);
	return (1);
}

void	to_append_or_not_to_append(char *value, t_envp *node, int a_flag)
{
	char	*appendage;

	if (!a_flag)
	{
		free(node->value);
		node->value = value;
	}
	else
	{
		appendage = ft_strjoin(node->value, value);
		free(value);
		free(node->value);
		node->value = appendage;
	}
}

int	extract_appendage(char *var, t_envp *envp, int to_extract)
{
	char	*key;
	char	*value;

	key = ft_substr(var, 0, to_extract - 1);
	if (!key)
		return (-1);
	value = ft_substr(var, to_extract + 1, ft_strlen(var + to_extract));
	if (!value)
	{
		free(key);
		return (-1);
	}
	if (node_check(key, value, envp, 1) == -1)
	{
		free(key);
		free(value);
		return (-1);
	}
	return (0);
}
