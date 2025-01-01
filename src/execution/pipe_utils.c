/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:00 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/01 12:29:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//NOTE: adding dup2 for stdin seems to make it go back to the cat in cat|cat|ls
//however process doesnt close, need to find solution

void	child_pipe(t_pipe *pipe_node, t_envp *envp, int *inp_pipe)
{
	if (dup2(inp_pipe[1], 1) == -1)
		exit_failure(envp->root, inp_pipe, envp);
	close(inp_pipe[1]);
	close(inp_pipe[0]);
	execution(pipe_node->left, 1, envp);
	close(1);
	exit(0);
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
}
