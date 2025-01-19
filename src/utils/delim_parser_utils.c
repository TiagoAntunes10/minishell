/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:58:10 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/19 17:06:07 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	receive_here_doc(t_delim *delim, t_tree *tree, t_envp *envp)
{
	int		inp_pipe[2];

	signal_ignore();
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	envp->id = fork();
	if (envp->id == -1)
	{
		close(inp_pipe[0]);
		close(inp_pipe[1]);
		free(delim->delim);
		free(delim);
		clear_tree(tree);
		return (-1);
	}
	if (envp->id == 0 && delim->delim[0] != 0)
		prep_heredoc(delim, tree, inp_pipe, envp);
	delim->fd = inp_pipe[0];
	close(inp_pipe[1]);
	if (heredoc_wait(envp, delim, tree) == -1)
		return (-1);
	return (0);
}

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
