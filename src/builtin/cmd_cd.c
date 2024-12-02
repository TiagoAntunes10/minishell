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

//TODO: handle ~ as $HOME cd ~/dir example OBS.: not normally implemented
//TODO: verify that cd with no args works with envp as expected
//TODO: make sure the allocated string with strjoin doesnt cause issues.

static int ft_changedir(char *path, t_envp *envp)
{
	char	*newvalue;
	char	*oldvalue;

	if (!(oldvalue = getcwd(NULL, 4096)))
		return (-1);
	if (chdir(path) == -1)
	{
		free(oldvalue);
		return (-1);
	}
	export_env(ft_strjoin("OLDPWD=", oldvalue), envp);
	if (oldvalue)
		free(oldvalue);
	if (!(newvalue = getcwd(NULL, 4096))) 
		return (-1);
	export_env(ft_strjoin("PWD=", newvalue), envp);
	if (newvalue)
		free(newvalue);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_envp *envp)
{
	struct stat	stats;

	if (cmd->opt[1] && cmd->opt[2])
		return (ft_putstr_fd(RED CD_ERR_ARG RST, STDERR_FILENO), 2);
	if (!cmd->opt[1] || !ft_strncmp(cmd->opt[1], "~", 1))
	{
		if (ft_changedir(search_envp(envp, "HOME")->value, envp) == -1)
			return (ft_putstr_fd(RED CD_GEN_ERR RST, STDERR_FILENO), 127);
		return (EXIT_SUCCESS);
	}
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
