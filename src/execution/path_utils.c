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

	cwd = getcwd(NULL, 4096);
	if (cwd == NULL)
	{
		if (search_envp(envp, "PWD"))
			cwd = search_envp(envp, "PWD")->value;
		else
			return (ft_strdup(cmd + 2));
	}
	cmd_path = ft_strjoin(cwd, cmd + 1);
	if (!cmd_path)
	{
		free(cwd);
		exit_failure(envp->root, NULL, envp);
	}
	free(cwd);
	return (cmd_path);
}

int	is_exec_dir(char *path, char *cmd)
{
	struct stat	stats;

	if (stat(path, &stats) == -1)
		return (1);
	if (S_ISDIR(stats.st_mode))
	{
		ft_putstr_fd(RED ERR_IS_DIR, 2);
		ft_putstr_fd(cmd, 2);
		stat_ret(": Is a directory\n"RST, 126);
		return (1);
	}
	else if (S_ISREG(stats.st_mode))
		return (0);
	return (0);
}
