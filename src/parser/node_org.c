/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_org.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:41 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/04 22:19:00 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

static t_tree	*org_pipe(t_tree *tree, t_tree *cmd)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	pipe->right = cmd;
	return ((t_tree *) pipe);
}

static t_tree	*org_list(t_tree *tree, t_tree *cmd)
{
	t_lst	*lst;

	lst = (t_lst *) tree;
	lst->right = cmd;
	return ((t_tree *) lst);
}

// TODO: Not sure if it should return NULL
t_tree	*org_tree(t_tree *tree, t_tree *cmd)
{
	if (tree == NULL)
		return ((t_tree *) cmd);
	else if (tree->type == PIPE)
		return (org_pipe(tree, cmd));
	else if (tree->type == LIST)
		return (org_list(tree, cmd));
	return (NULL);
}