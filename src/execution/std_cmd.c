/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/11 15:23:51 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*search_path(char *cmd, char **envp_path, t_envp *envp)
{
	char	*cmd_path;
	int		size;
	int		i;

	i = -1;
	if (cmd[0] == 0)
		return (NULL);
	while (envp_path[++i] != NULL)
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
		cmd_path = NULL;
	}
	clear_arr(envp_path);
	return (cmd_path);
}

static char	*find_path(char *cmd, t_envp *envp)
{
	char		*cmd_path;
	char		**envp_path;

	if (cmd[0] == '.' && cmd[1] == '/')
		cmd_path = relative_path(cmd, envp);
	else if (cmd[0] == '/')
		cmd_path = ft_strdup(cmd);
	else
	{
		cmd_path = NULL;
		if (search_envp(envp, "PATH"))
		{
			envp_path = ft_split(search_envp(envp, "PATH")->value, ':');
			cmd_path = search_path(cmd, envp_path, envp);
		}
	}
	if (cmd_path != NULL && is_exec_dir(cmd_path, cmd))
	{
		ft_free(cmd_path);
		exit_failure(envp->root, NULL, envp);
	}
	return (cmd_path);
}

static void	exec_error(t_envp *envp_lst, char *cmd_path, char **envp_arr,
		char *cmd)
{
	if ((errno == ENOENT || errno == ENOEXEC) && (errno != EACCES))
	{
		ft_putstr_fd(RED "minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		stat_ret(": command not found\n" RST, 127);
	}
	else
		g_exit_code = 126;
	if (cmd_path)
		free(cmd_path);
	clear_arr(envp_arr);
	exit_failure(envp_lst->root, NULL, envp_lst);
}

static void	std_cmd_error(t_envp *envp, char *msg, int fd)
{
	if (fd == 2)
	{
		stat_ret(msg, fd);
		exit_failure(envp->root, NULL, envp);
	}
	else if (fd == 0)
	{
		stat_ret(msg, fd);
		exit_success(envp->root, -1, envp);
	}
}

void	std_cmd(t_cmd *cmd, t_envp *envp)
{
	char	**envp_arr;
	char	*cmd_path;
	pid_t	id;

	if (*(cmd->cmd) == ';' && ft_strlen(cmd->cmd) == 1)
		std_cmd_error(envp, "syntax error near unexpected token ';'\n", 2);
	if (cmd->cmd[0] == '\0')
		std_cmd_error(envp, NULL, 0);
	cmd_path = find_path(cmd->cmd, envp);
	envp_arr = lst_to_arr(envp);
	if (cmd_path == NULL)
		return (exec_error(envp, NULL, envp_arr, cmd->cmd));
	if (envp->id == 0)
		signal_decider((t_tree *)cmd);
	id = fork();
	if (id == -1)
		exit_failure(envp->root, NULL, envp);
	else if (id == 0)
	{
		if (execve(cmd_path, cmd->opt, envp_arr) == -1)
			exec_error(envp, cmd_path, envp_arr, cmd->cmd);
	}
	clear_std_cmd(envp, cmd_path, envp_arr);
	exec_wait(id);
}
