/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/22 22:09:12 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*search_path(char *cmd, char **envp_path, t_envp *envp)
{
	char	*cmd_path;
	int		size;
	int		i;

	i = 0;
	while (envp_path[i] != NULL)
	{
		size = ft_strlen(cmd) + ft_strlen(envp_path[i]) + 2;
		cmd_path = (char *) safe_alloc(size, 1, envp->root, envp);
		if (cmd_path == NULL)
			exit_failure(envp->root, NULL, envp);
		ft_strlcat(cmd_path, envp_path[i], ft_strlen(envp_path[i]) + 1);
		ft_strlcat(cmd_path, "/", ft_strlen(envp_path[i]) + 2);
		ft_strlcat(cmd_path, cmd, size + 1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(cmd_path);
		i++;
	}
	clear_arr(envp_path);
	return (cmd_path);
}

static char	*find_path(char *cmd, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_path;

	if (access(cmd, F_OK) == -1)
	{
		envp_path = ft_split(search_envp(envp, "PATH")->value, ':');
		cmd_path = search_path(cmd, envp_path, envp);
	}
	else
	{
		if (access(cmd, X_OK) == -1)
		{
			if (errno == EACCES)
				g_exit_code = 126;
			exit_failure(envp->root, NULL, envp);
		}
		cmd_path = ft_substr(cmd, 0, ft_strlen(cmd));
		if (cmd_path == NULL)
			exit_failure(envp->root, NULL, envp);
	}
	return (cmd_path);
}

void	std_cmd(t_cmd *cmd, t_envp *envp)
{
	char	**envp_arr;
	char	*cmd_path;

	if (*(cmd->cmd) == ';' && ft_strlen(cmd->cmd) == 1)
	{
		stat_ret("syntax error near unexpected token ';'\n", 2);
		exit_failure(envp->root, NULL, envp);
	}
	get_full_str(cmd, envp);
	envp_arr = lst_to_arr(envp);
	cmd_path = find_path(cmd->cmd, envp);
	if (execve(cmd_path, cmd->opt, envp_arr) == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit_code = 127;
		}
		else
			g_exit_code = 126;
		exit_failure(envp->root, NULL, envp);
	}
}
