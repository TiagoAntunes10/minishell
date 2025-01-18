/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:49:12 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 21:23:37 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	delim_redir_switch(t_redir *redir, t_tree *tree)
{
	t_delim	*delim_tree;

	delim_tree = (t_delim *) tree;
	while (delim_tree->right != NULL && delim_tree->right->type == DELIM)
		delim_tree = (t_delim *) delim_tree->right;
	redir->right = delim_tree->right;
	delim_tree->right = (t_tree *) redir;
}

void	tree_leafs_pipe(t_tree *tree, t_pipe *pipe)
{
	t_pipe	*tree_pipe;

	tree_pipe = (t_pipe *) tree;
	while (tree_pipe->right != NULL && tree_pipe->right->type == PIPE)
		tree_pipe = (t_pipe *) tree_pipe->right;
	pipe->left = tree_pipe->right;
	tree_pipe->right = (t_tree *) pipe;
}

int	check_cmd(t_tree *tree)
{
	t_pipe	*pipe;
	t_redir	*redir;
	t_delim	*delim;

	if (tree == NULL)
		return (0);
	else if (tree->type == CMD)
		return (1);
	else if (tree->type == PIPE)
	{
		pipe = (t_pipe *) tree;
		return (check_cmd(pipe->right));
	}
	else if (tree->type == REDIR)
	{
		redir = (t_redir *) tree;
		return (check_cmd(redir->right));
	}
	else if (tree->type == DELIM)
	{
		delim = (t_delim *) tree;
		return (check_cmd(delim->right));
	}
	return (0);
}

void	tree_leafs_redir(t_tree *tree, t_redir *redir)
{
	t_pipe	*tree_pipe;
	t_redir	*tree_redir;

	tree_pipe = (t_pipe *) tree;
	while (tree_pipe->right != NULL && tree_pipe->right->type == PIPE)
		tree_pipe = (t_pipe *) tree_pipe->right;
	if (tree_pipe->right != NULL && tree_pipe->right->type == REDIR)
	{
		tree_redir = (t_redir *) tree_pipe->right;
		while (tree_redir->right != NULL && tree_redir->right->type == REDIR)
			tree_redir = (t_redir *) tree_redir->right;
		redir->right = tree_redir->right;
		tree_redir->right = (t_tree *) redir;
	}
	else if (tree_pipe->right != NULL && tree_pipe->right->type == CMD)
	{
		redir->right = tree_pipe->right;
		tree_pipe->right = (t_tree *) redir;
	}
	else
		tree_pipe->right = (t_tree *) redir;
}
