/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 21:31:34 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exec_pipe(t_tree *tree, int fd, t_envp *envp)
{
	int		inp_pipe[2];
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *) tree;
	if (pipe_node->left == NULL || pipe_node->right == NULL)
	{
		ft_putstr_fd(RED PIPE_ERR RST, 2);
		g_exit_code = 2;
		exit_failure(envp->root, NULL, envp);
	}
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	signal_ignore();
	envp->id = fork();
	if (envp->id == -1)
		exit_failure(envp->root, inp_pipe, envp);
	else if (envp->id == 0)
	{
		signal_decider(tree);
		pipe_in_pipe(inp_pipe, fd, envp);
		execution(pipe_node->right, 0, envp);
	}
	child_pipe(pipe_node, envp, inp_pipe);
}

void	exec_delim(t_tree *tree, t_envp *envp)
{
	t_delim	*delim;
	// int		inp_pipe[2];

	delim = (t_delim *) tree;
	// if (isatty(1) != 1 || envp->w_pipe == 1)
	// 	envp->w_pipe = dup(1);
	// signal_heredoc();
	if (delim->fd != -1)
	{
		if (dup2(delim->fd, 0) == -1)
			exit_failure(envp->root, NULL, envp);
		close(delim->fd);
	}
	// if (envp->w_pipe != -1)
	// {
	// 	if (dup2(envp->w_pipe, 1) == -1)
	// 		exit_failure(envp->root, inp_pipe, envp);
	// 	close(envp->w_pipe);
	// 	envp->w_pipe = 1;
	// }
	// close(inp_pipe[1]);
	// close(inp_pipe[0]);
	execution(delim->right, 0, envp);
	close(0);
}

//> = 65 | >> = 1089 | < = 0
void	exec_redir(t_tree *tree, t_envp *envp)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	if (is_redir_valid(redir->file) == 0)
		exit_failure(envp->root, NULL, envp);
	quotes_pairs(redir->file, envp, 0);
	remove_quotes(&(redir->file), 0, envp);
	if (redir->mode == O_RDONLY)
		redir_read(redir, envp);
	else
		redir_write(redir, envp);
}
