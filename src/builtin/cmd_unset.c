/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:01:08 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/04 20:41:43 by rapcampo         ###   ########.fr       */
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
/*
static int	is_value_node(t_envp *node)
{
	if (node && (node->id || node->fd_in || node->fd_out))
		return (1);
	return (0);
}

static void	clone_node(t_envp *prev, t_envp *rem)
{
	t_envp	*to_clone;

	if (rem && rem->next == NULL)
	{
		if (!is_value_node(rem) && prev)
		{
			prev->next = NULL;
			ft_delnode(rem);
		}
		return ;
	}
	to_clone = rem->next;
	if (to_clone->next != NULL)
		rem->next = to_clone->next;
	ft_free(rem->key);
	ft_free(rem->value);
	rem->key = ft_strdup(to_clone->key);
	rem->value = ft_strdup(to_clone->value);
	ft_delnode(to_clone);
}
*/
static void	unset_env(char *key, t_envp **head)
{
	t_envp	*prev;
	t_envp	*temp;

	//prev = NULL;
	prev = *head;
	temp = (*head)->next;
/*	if (!prev && !ft_strncmp(temp->key, key, ft_strlen(key)))
	{
		clone_node(NULL, temp);
		return ;
	}*/
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
		{
			prev->next = temp->next;
			ft_delnode(temp);
		//	clone_node(prev, temp);
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
