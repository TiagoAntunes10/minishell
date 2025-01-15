/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:36:37 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/09 21:02:23 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*relative_path(char *cmd, t_envp *envp)
{
	char	*cwd;
	char	*cmd_path;

	is_odd_case(envp, cmd);
	cwd = getcwd(NULL, 4096);
	if (cwd == NULL)
	{
		if (search_envp(envp, "PWD"))
			cwd = ft_strdup(search_envp(envp, "PWD")->value);
		else
			cwd = ft_strdup("");
	}
	cmd_path = ft_strjoin(cwd, cmd + 1);
	if (!cmd_path)
	{
		free(cwd);
		exit_failure(envp->root, NULL, envp);
	}
	free(cwd);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (ft_strdup(cmd + 2));
}

int	is_exec_dir(char *path, char *cmd)
{
	struct stat	stats;

	if (path == NULL)
		return (0);
	if (stat(path, &stats) == -1)
	{
		ft_putstr_fd(RED ERR_IS_DIR, 2);
		ft_putstr_fd(cmd, 2);
		stat_ret(": no such file or directory\n"RST, 127);
		return (1);
	}
	if (S_ISDIR(stats.st_mode))
	{
		ft_putstr_fd(RED ERR_IS_DIR, 2);
		ft_putstr_fd(cmd, 2);
		stat_ret(": Is a directory\n"RST, 126);
		return (1);
	}
	else if (S_ISREG(stats.st_mode))
		return (0);
	return (1);
}

void	is_odd_case(t_envp *envp, char *cmd)
{
	if (ft_strncmp(cmd, ".", ft_strlen(cmd)) == 0)
		std_cmd_error(envp, RED REL_PATH_ERR REL_USAGE RST, 2);
	else if (ft_strncmp(cmd, "..", ft_strlen(cmd)) == 0)
	{
		if (search_envp(envp, "PATH"))
			std_cmd_error(envp, RED"..: command not found\n"RST, 127);
		else
			std_cmd_error(envp, RED"..: Is a directory\n"RST, 126);
	}
}
