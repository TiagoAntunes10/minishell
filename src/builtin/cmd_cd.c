/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:35 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/21 03:39:28 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	ft_changedir(char *path, t_envp *envp)
{
	char	*newvalue;
	char	*oldvalue;
	char	*buffer;

	oldvalue = getcwd(NULL, 4096);
	if (!oldvalue)
		return (-1);
	if (chdir(path) == -1)
		return (free(oldvalue), -1);
	buffer = ft_strjoin("OLDPWD=", oldvalue);
	if (!buffer)
		return (free(oldvalue), -1);
	export_env(buffer, envp);
	free(buffer);
	free(oldvalue);
	newvalue = getcwd(NULL, 4096);
	if (!newvalue)
		return (-1);
	buffer = ft_strjoin("PWD=", newvalue);
	if (!buffer)
		return (free(newvalue), -1);
	export_env(buffer, envp);
	free(buffer);
	free(newvalue);
	return (EXIT_SUCCESS);
}

static int	cd_err_handler(void)
{
	if (errno == EACCES)
		return (stat_ret(RED CD_NO_PERM RST, 126));
	else if (errno == ENOENT)
		return (stat_ret(RED CD_NOT_FND RST, 127));
	else if (errno != 0)
	{
		stat_ret(strerror(errno), 1);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	else
		return (stat_ret(RED CD_GEN_ERR RST, 1));
}

static char	*get_truepath(char *home, char *path)
{
	char	*truepath;

	if (path[0] == '~')
	{
		truepath = ft_strjoin(home, path + 1);
		if (!truepath)
			return (NULL);
	}
	else
	{
		truepath = ft_strdup(path);
		if (!truepath)
			return (NULL);
	}
	return (truepath);
}

static int	cd_checkups(char *path, t_envp *envp)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		if (ft_changedir(path, envp) == -1)
		{
			free(path);
			return (cd_err_handler());
		}
	}
	else
	{
		free(path);
		return (stat_ret(RED CD_NOT_DIR RST, 1));
	}
	free(path);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_envp *envp)
{
	int	err;

	err = 0;
	if (cmd->opt[1] && cmd->opt[2])
		return (stat_ret(RED CD_ERR_ARG RST, 2));
	if (!cmd->opt[1] || !ft_strncmp(cmd->opt[1], "~", lencmp(cmd->opt[1], "~")))
	{
		if (!search_envp(envp, "HOME")
				|| ft_changedir(search_envp(envp, "HOME")->value, envp) == -1)
			return (stat_ret(RED CD_NO_HOME RST, 1));
	}
	else if (!ft_strncmp(cmd->opt[1], "-", lencmp(cmd->opt[1], "-")))
	{
		if (!search_envp(envp, "OLDPWD")
				|| ft_changedir(search_envp(envp, "OLDPWD")->value, envp) == -1)
			return (stat_ret(RED CD_OLDPWD RST, 1));
	}
	else
	{
		err = cd_checkups(get_truepath(search_envp(envp, "HOME")->value,
					cmd->opt[1]), envp);
		if (err)
			return (err);
	}
	return (stat_ret(NULL, 0));
}
