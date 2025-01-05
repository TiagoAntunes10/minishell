/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/05 22:57:39 by tialbert         ###   ########.fr       */
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
	if (envp_path[i] == NULL)
		return (clear_arr(envp_path), NULL);
	clear_arr(envp_path);
	return (cmd_path);
}

static char	*find_path(char *cmd, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_path;

	if (access(cmd, F_OK) == -1)
	{
		if (!search_envp(envp, "PATH"))
			exit_failure(envp->root, NULL, envp);
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

static void	exec_error(t_envp *envp_lst, char *cmd_path, char **envp_arr,
		char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(RED "minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n" RST, STDERR_FILENO);
		g_exit_code = 127;
	}
	else
		g_exit_code = 126;
	if (cmd_path)
		free(cmd_path);
	clear_arr(envp_arr);
	exit_failure(envp_lst->root, NULL, envp_lst);
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
	if (cmd->cmd[0] == '\0')
	{
		stat_ret(NULL, 0);
		exit_success(envp->root, -1, envp);
	}
	envp_arr = lst_to_arr(envp);
	cmd_path = find_path(cmd->cmd, envp);
	if (cmd_path == NULL)
		return (exec_error(envp, NULL, envp_arr, cmd->cmd));
	if (execve(cmd_path, cmd->opt, envp_arr) == -1)
		exec_error(envp, cmd_path, envp_arr, cmd->cmd);
}
