/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:27:00 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/30 22:27:38 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	child_pipe(t_pipe *pipe_node, t_envp *envp, int *inp_pipe)
{
	if (dup2(inp_pipe[1], 1) == -1)
	{
		close(inp_pipe[0]);
		close(inp_pipe[1]);
		exit(errno);
	}
	close(inp_pipe[1]);
	execution(pipe_node->left, 1, envp);
	close(inp_pipe[0]);
	close(1);
	exit(0);
}

void	pipe_in_pipe(int *inp_pipe, int fd)
{
	if (dup2(inp_pipe[0], 0) == -1)
	{
		close(inp_pipe[0]);
		if (fd == 1)
			close(fd);
		exit(errno);
	}
	close(inp_pipe[0]);
}
