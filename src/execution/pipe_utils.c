/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:00 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/15 21:36:45 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	child_pipe(t_pipe *pipe_node, t_envp *envp, int *inp_pipe)
{
	if (dup2(inp_pipe[1], 1) == -1)
		exit_failure(envp->root, inp_pipe, envp);
	close(inp_pipe[1]);
	close(inp_pipe[0]);
	envp->w_pipe = 1;
	execution(pipe_node->left, 1, envp);
}

void	pipe_in_pipe(int *inp_pipe, int fd, t_envp *envp)
{
	if (dup2(inp_pipe[0], 0) == -1)
	{
		if (fd == 1)
			close(fd);
		exit_failure(envp->root, inp_pipe, envp);
	}
	close(inp_pipe[1]);
	close(inp_pipe[0]);
	envp->w_pipe = -1;
	envp->r_pipe = 0;
}
