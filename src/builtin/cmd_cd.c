/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:35 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/14 20:33:42 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include <asm-generic/errno-base.h>

//TODO: handle ~ as $HOME cd ~/dir example
//TODO: handle envs so to update PWD and OLDPWD

static int ft_changedir(char *path, t_envlist *envp)
{
		
}

int	ft_cd(t_cmd *cmd, t_envlist *envp)
{
	struct stat	stats;

//	if (access(cmd->opt[0], F_OK) != 0 && access(cmd->opt[0], X_OK) != 0)
	if (cmd->opt[1] && cmd->opt[2])
		return (ft_putstr_fd(RED CD_ERR_ARG RST, STDERR_FILENO), 2);
	if (cmd->opt[0] && !cmd->opt[1])
		return (chdir(getenv("HOME")), 0);
	stat(cmd->opt[1], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		if (ft_changedir(cmd->opt[1], envp) == -1)
		{
			if (errno == EACCES)
				return (ft_putstr_fd(RED CD_NO_PERM RST, STDERR_FILENO), 2);
			else
				return (ft_putstr_fd(RED CD_GEN_ERR RST, STDERR_FILENO), 127);
		}
	}
	else
		return (ft_putstr_fd(RED CD_NOT_DIR RST, STDERR_FILENO), 2);
	return (EXIT_SUCCESS);
}
