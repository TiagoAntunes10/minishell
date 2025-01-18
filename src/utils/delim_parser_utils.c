/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:58:10 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 21:22:32 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	tree_leafs_delim(t_tree *tree, t_delim *delim)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	while (pipe->right != NULL && pipe->right->type == PIPE)
		pipe = (t_pipe *) pipe->right;
	if (pipe->right != NULL && pipe->right->type == REDIR)
		org_delim(delim, pipe->right);
	else if (pipe->right != NULL && pipe->right->type == DELIM)
		org_delim(delim, pipe->right);
	else
	{
		delim->right = pipe->right;
		pipe->right = (t_tree *) delim;
	}
}

static void	order_delim(t_tree *tree, t_delim *delim)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	while (redir->right != NULL && redir->right->type == REDIR)
		redir = (t_redir *) redir->right;
	if (delim->right != NULL && delim->right->type == DELIM)
		org_delim(delim, delim->right);
	else
	{
		delim->right = redir->right;
		redir->right = (t_tree *) delim;
	}
}

t_tree	*org_delim(t_delim *delim, t_tree *tree)
{
	t_delim	*tree_delim;

	if (tree == NULL)
		return ((t_tree *) delim);
	else if (tree->type == REDIR)
		order_delim(tree, delim);
	else if (tree->type == PIPE)
		tree_leafs_delim(tree, delim);
	else if (tree->type == DELIM)
	{
		tree_delim = (t_delim *) tree;
		delim->right = tree_delim->right;
		tree_delim->right = (t_tree *) delim;
	}
	else
	{
		delim->right = tree;
		tree = (t_tree *) delim;
	}
	return (tree);
}
