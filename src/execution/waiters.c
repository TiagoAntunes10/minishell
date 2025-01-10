/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:21:51 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/09 22:24:57 by tialbert         ###   ########.fr       */
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
