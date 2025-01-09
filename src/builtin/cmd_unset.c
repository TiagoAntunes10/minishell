/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:01:08 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/09 22:46:45 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: verify node delition
//TODO: check if using a loop for multiple args in unset is the best way
//NOTE!! unset on bash and c function unsetenv(const char *env) both does not
//seem to do much if no arguments or options are presented, and mostly always
//returns sucess. Only error seems to be related to not being able to allocate
//more memory.

static void	ft_delnode(t_envp *node)
{
	if (!node || node == 0)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

static void	unset_env(char *key, t_envp **head)
{
	t_envp	*prev;
	t_envp	*temp;

	prev = *head;
	temp = (*head)->next;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
		{
			prev->next = temp->next;
			ft_delnode(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(t_cmd *cmd, t_envp *envp)
{
	int	i;

	i = 0;
	if (cmd->opt[0] && !cmd->opt[1])
		return (stat_ret(NULL, 0));
	while (cmd->opt[++i])
	{
		if (search_envp(envp, cmd->opt[i]) == NULL)
			continue ;
		unset_env(cmd->opt[i], &envp);
	}
	return (stat_ret(NULL, 0));
}
