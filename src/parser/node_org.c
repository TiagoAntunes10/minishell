/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_org.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:41 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/17 22:30:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	check_outfile(t_redir *redir, int mode, t_envp *envp, t_tree *tree)
{
	int		redir_fd;
	t_redir	*redir_node;

	redir_node = NULL;
	if (quotes_pairs(redir->file, envp, 1) == -1)
		return ;
	remove_quotes(&(redir->file), 0, envp);
	if (tree != NULL && tree->type == REDIR)
		redir_node = (t_redir *) tree;
	if (redir_node != NULL && access(redir_node->file, F_OK | R_OK) == -1)
		return ;
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
		while (tree_node->right != NULL && tree_node->right->type == REDIR)
			tree_node = (t_redir *) tree_node->right;
		redir->right = tree_node->right;
		tree_node->right = (t_tree *) redir;
	}
	else if (tree->type == DELIM)
		delim_redir_switch(redir, tree);
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
