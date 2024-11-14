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
#include <unistd.h>

//TODO check if int fd is needed or not
//TODO check if better to use errno for access rights

int	ft_cd(t_cmd *cmd)
{
	struct stat	stats;

//	if (access(cmd->opt[0], F_OK) != 0 && access(cmd->opt[0], X_OK) != 0)
	if (cmd->opt[0] && cmd->opt[1])
		return (ft_putstr_fd("cd: Error too many args\n", 2), 2);
	if (cmd->cmd && !cmd->opt)
		return (chdir(getenv("HOME")), 0);
	stat(cmd->opt[0], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		if (chdir(cmd->opt[0]) == -1)
		{
			if (errno == EACCES)
				return (ft_putstr_fd("cd: Error no permission\n", 2), 2);
			else
				return (ft_putstr_fd("cd: Error could not change directory\n", 2), 127);
		}
	}
	else
		return (ft_putstr_fd("cd: Error is not a directory\n", 2), 2);
	return (0);
}
