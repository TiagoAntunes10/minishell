/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:21:51 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/19 16:34:31 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	child_wait(t_envp *envp)
{
	int	status;

	if (waitpid(envp->id, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		signal_parent();
		envp->id = 0;
	}
}

void	exec_wait(pid_t id)
{
	int	status;

	if (waitpid(id, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}

int	heredoc_wait(t_envp *envp, t_delim *delim, t_tree *tree)
{
	int	status;

	if (waitpid(envp->id, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		envp->id = 0;
		signal_parent();
		if (g_exit_code != 0)
		{
			free(delim->delim);
			close(delim->fd);
			free(delim);
			clear_tree(tree);
			return (-1);
		}
		return (0);
	}
	return (0);
}
