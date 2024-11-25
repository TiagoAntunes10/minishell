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
//TODO: edge case handling if head node is to be deleted

static void	ft_delnode(t_envp *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node->next)
		free(node->next);
	if (node)
		free(node);
}

int	ft_unset(t_cmd *cmd, t_envp *envp)
{
	t_envp	*prev;
	t_envp	*curr;

	prev = NULL;
	while (curr)
	{
		if ()	
	}
	return (EXIT_SUCCESS);
}
