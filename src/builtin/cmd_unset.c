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
#include <stdlib.h>

//TODO: verify node delition
//TODO: ERROR handling?
//TODO: check if using a loop for multiple args in unset is the best way

static void	ft_delnode(t_envp *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

static void	unset_env(char *key, t_envp *head)
{
	t_envp	*prev;
	t_envp	*temp;

	prev = NULL;
	temp = head;
	if (!prev && !ft_strncmp(temp->key, key, ft_strlen(key)))
	{
		head = temp->next;
		ft_delnode(temp);
		return ;
	}
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
		{
			prev->next = temp->next;
			ft_delnode(temp);
			break ;
		}
		prev->next = temp;
		temp = temp->next;
	}
}

int	ft_unset(t_cmd *cmd, t_envp *envp)
{
	int	i;

	i = 0;
	if (cmd->opt[0] && !cmd->opt[1])
		return (EXIT_SUCCESS);
	while (cmd->opt[++i])
		unset_env(cmd->opt[i], envp);
	return (EXIT_SUCCESS);
}
