/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/07 22:34:11 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	exec_pipe(t_tree *tree, int *fd)
{
	int		*inp_pipe;
	int		id;
	t_pipe	*pipe_node;
	int		status;

	id = fork();
	if (id == -1)
		return ;
	else if (id == 0)
	{
		pipe_node = (t_pipe *) tree;
		// TODO: Not sure if this should exit
		if (pipe(inp_pipe) == -1)
			exit(1);
		id = fork();
		if (id == -1)
			exit(1);
		else if (id == 0)
		{
			if (dup2(inp_pipe[1], 1) == -1)
			{
				close(inp_pipe[0]);
				close(inp_pipe[1]);
				exit(1);
			}
			execution(pipe_node->left, inp_pipe);
		}
		waitpid(-1, &status, WNOHANG);
		if (fd != NULL)
		{
			close(inp_pipe[1]);
			inp_pipe[1] = fd[1];
			if (dup2(inp_pipe[1], 1) == -1 || dup2(inp_pipe[0], 0) == -1)
			{
				close(inp_pipe[0]);
				// TODO: Check if I should close this end of the pipe here
				close(inp_pipe[1]);
				exit(1);
			}
		}
		else
		{
			close(inp_pipe[1]);
			if (dup2(inp_pipe[0], 0) == -1)
			{
				close(inp_pipe[0]);
				exit(1);
			}
		}
		execution(pipe_node->right, inp_pipe);
	}
	waitpid(-1, &status, WNOHANG);
	return ;
}
