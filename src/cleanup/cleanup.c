/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/11 17:00:18 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	clean_cmd(t_tree *cmd, t_tree *tree, t_envp *envp)
{
	clear_tree(cmd);
	exit_failure(tree, NULL, envp);
}

void	clear_envp(t_envp *envp)
{
	t_envp	*envp_cpy;

	if (!envp || envp == 0)
		return ;
	if (envp->r_pipe != -1)
		close(envp->r_pipe);
	if (envp->w_pipe != -1)
		close(envp->w_pipe);
	if (envp->fd_in != 0)
		close(envp->fd_in);
	if (envp->fd_out != 0)
		close(envp->fd_out);
	while (envp != NULL)
	{
		if (envp->key != NULL)
			free(envp->key);
		if (envp->value != NULL)
			free(envp->value);
		if (envp->input_arr != NULL)
			clear_arr(envp->input_arr);
		envp_cpy = envp->next;
		ft_free(envp);
		envp = envp_cpy;
	}
}

char	**clear_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

void	exit_success(t_tree *tree, int fd, t_envp *envp)
{
	if (tree != NULL)
		clear_tree(tree);
	if (envp != NULL)
		clear_envp(envp);
	if (fd != -1)
		close(fd);
	exit(g_exit_code);
}

void	exit_failure(t_tree *tree, int *fd, t_envp *envp)
{
	int		i;
	t_cmd	*cmd;

	if (tree->type == CMD && errno != 25)
	{
		cmd = (t_cmd *)tree;
		if (errno && !(errno == ENOENT && g_exit_code == 127)
			&& errno != ENOEXEC && errno != EACCES)
			perror(cmd->cmd);
	}
	if (tree != NULL)
		clear_tree(tree);
	if (envp != NULL)
		clear_envp(envp);
	if (fd != NULL)
	{
		i = 0;
		while (i < 2)
			close(fd[i++]);
	}
	if (g_exit_code == 0)
		g_exit_code = 1;
	exit(g_exit_code);
}
