/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:52:52 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/06 15:32:15 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	clear_pipe(t_tree *tree)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	clear_tree(pipe->left);
	clear_tree(pipe->right);
	free(tree);
}

static void	clear_delim(t_tree *tree)
{
	t_delim	*delim;

	delim = (t_delim *) tree;
	clear_tree(delim->right);
	free(delim->delim);
	free(tree);
}

static void	clear_redir(t_tree *tree)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	clear_tree(redir->right);
	free(redir->file);
	free(tree);
}

void	clear_tree(t_tree *tree)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		clear_pipe(tree);
	else if (tree->type == DELIM)
		clear_delim(tree);	
	else if (tree->type == REDIR)
		clear_redir(tree);
	else if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (cmd->opt != NULL)
			clear_arr(cmd->opt);
		if (cmd->cmd != NULL)
			free(cmd->cmd);
		free(tree);
	}
}
