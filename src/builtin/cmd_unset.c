/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:01:08 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/25 00:02:12 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: verify node delition
//TODO: linking nodes if middle node is unset
//TODO: ERROR handling?

static void	ft_delnode(t_envp *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

int	ft_unset(t_cmd *cmd, t_envp *envp)
{
	t_envp	*prev;
	t_envp	*temp;

	prev = NULL;
	temp = envp;
	if (!prev && !ft_strncmp(temp->key, cmd->opt[1], ft_strlen(cmd->opt[1])))
	{
		envp = temp->next;
		ft_delnode(temp);
		return (EXIT_SUCCESS);
	}
	while (temp)
	{
		if (!ft_strncmp(temp->key, cmd->opt[1], ft_strlen(cmd->opt[1])))
		{
			prev->next = temp->next;
			ft_delnode(temp);
			break ;
		}
		prev->next = temp;
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
