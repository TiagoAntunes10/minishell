/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_org.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:41 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/18 15:58:58 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	check_outfile(char *input, int mode, t_tree *tree, t_envp *envp)
{
	int	redir_fd;

	if (access(input, F_OK) == 0)
	{
		if (unlink(input) == -1)
			exit_failure(tree, NULL, envp);
	}
	redir_fd = open(input, mode, 0755);
	if (redir_fd == -1)
		exit_failure(tree, NULL, envp);
	write(redir_fd, "\0", 1);
	close(redir_fd);
}

static t_tree	*org_pipe(t_tree *tree, t_tree *cmd)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	pipe->right = cmd;
	return ((t_tree *) pipe);
}

static t_tree	*org_redir(t_tree *tree, t_tree *cmd)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	redir->right = cmd;
	return ((t_tree *) redir);
}

// TODO: Not sure if it should return NULL
t_tree	*org_tree(t_tree *tree, t_tree *cmd)
{
	if (tree == NULL)
		return ((t_tree *) cmd);
	else if (tree->type == PIPE)
		return (org_pipe(tree, cmd));
	else if (tree->type == REDIR)
		return (org_redir(tree, cmd));
	return (NULL);
}
