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
//TODO: verify that getcwd changes its return value after execution of chdir
//TODO: verify that cd with no args works with envp as expected

static int ft_changedir(char *path, t_envp *envp)
{
	t_envp	*oldpwd;
	t_envp	*pwd;
	char	*oldvalue;

	oldpwd = search_envp(envp, "OLDPWD");
	pwd = search_envp(envp, "PWD");
	oldvalue = getcwd(NULL, 4096);
	if (chdir(path) == -1)
	{
		free(oldvalue);
		return (-1;
	}
	free(oldpwd->value);
	oldpwd->value = NULL;
	oldpwd->value = oldvalue;
	free(pwd->value);
	pwd->value = NULL;
	pwd->value = getcwd(NULL, 4096); 
	free(oldvalue);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envp *envp)
{
	struct stat	stats;

	if (cmd->opt[1] && cmd->opt[2])
		return (ft_putstr_fd(RED CD_ERR_ARG RST, STDERR_FILENO), 2);
	if (cmd->opt[0] && !cmd->opt[1])
	{
		if (ft_changedir(getenv("HOME"), envp) == -1)
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
