/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_org.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:41 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/06 20:50:21 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	check_outfile(t_redir *redir, int mode)
{
	int	redir_fd;

	if (access(redir->file, F_OK) == 0)
	{
		if (unlink(redir->file) == -1)
			return ;
	}
	redir_fd = open(redir->file, mode, 0755);
	if (redir_fd == -1)
		return ;
	write(redir_fd, "\0", 1);
	close(redir_fd);
}

t_tree	*org_redir_read(t_redir *redir, t_tree *tree)
{
	t_redir	*tree_node;

	if (tree == NULL)
		return ((t_tree *) redir);
	if (tree->type == REDIR)
	{
		tree_node = (t_redir *) tree;
		redir->right = tree_node->right;
		tree_node->right = (t_tree *) redir;
		return ((t_tree *) tree_node);
	}
	else if (tree->type == PIPE)
		tree_leafs_redir(tree, redir);
	else
	{
		redir->right = tree;
		tree = (t_tree *) redir;
	}
	return (tree);
}

static void	org_pipe(t_tree *tree, t_tree *cmd)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	if (pipe->right != NULL)
		return (org_tree((t_tree *) pipe->right, cmd));
	pipe->right = cmd;
}

static void	org_redir(t_tree *tree, t_tree *cmd)
{
	t_redir	*redir;
	t_delim	*delim;

	if (tree->type == REDIR)
	{
		redir = (t_redir *) tree;
		if (redir->right != NULL)
			return (org_tree((t_tree *) redir->right, cmd));
		redir->right = cmd;
	}
	else if (tree->type == DELIM)
	{
		delim = (t_delim *) tree;
		if (delim->right != NULL)
			return (org_tree((t_tree *) delim->right, cmd));
		delim->right = cmd;
	}
}

void	org_tree(t_tree *tree, t_tree *cmd)
{
	if (tree->type == PIPE)
		return (org_pipe(tree, cmd));
	else if (tree->type == REDIR || tree->type == DELIM)
		return (org_redir(tree, cmd));
}
