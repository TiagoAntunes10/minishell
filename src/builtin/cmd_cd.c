/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:35 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/14 20:10:47 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO check if int fd is needed or not

#include "../../Include/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	struct stat	stats;

	if (!access(cmd->opt[0], F_OK) && !access(cmd->opt[0], X_OK))
		return (ft_putstr_fd("cd: Error no permission", 2), 2);
	if (cmd->opt[0] && cmd->opt[1])
		return (ft_putstr_fd("cd: Error too many args", 2), 2);
	stat(cmd->opt[0], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		if (chdir(cmd->opt[0]) == -1)
			return (ft_putstr_fd("cd: Error could not change directory", 2), 127);
	}
	else
		return (ft_putstr_fd("cd: Error is not a directory", 2), 2);
	return (0);
}
