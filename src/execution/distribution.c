/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/08 22:07:40 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	cmd_dist(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) tree;
	// if (ft_strncmp(cmd->cmd, "$", ft_strlen(cmd->cmd)))
	// 	dollar_sub(cmd, 0);
	// if (ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)))
	// 	ft_echo(cmd);
	// else if (ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)))
	// 	ft_pwd(fd);
	// else if (ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)))
	// 	ft_export(cmd);
	// else if (ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)))
	// 	ft_unset(cmd);
	// else if (ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)))
	// 	ft_env(cmd);
	// // TODO: The exit function will not be able to free the whole tree
	// else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)))
	// 	exit_success((t_tree *) cmd, 0);
	// else
	std_cmd(cmd, envp);
}

static void	exec_tree(t_tree *tree, int fd, t_envp *envp)
{
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		exec_pipe(tree, fd, envp);
	else if (tree->type == DELIM)
		exec_delim(tree, envp);	
	else if (tree->type == REDIR)
		exec_redir(tree, envp);
	else if (tree->type == CMD)
		cmd_dist(tree, envp);
}

void	execution(t_tree *tree, int fd, t_envp *envp)
{
	// t_cmd	*cmd;
	int		id;
	int		status;

	// cmd = NULL;
	// if (tree->type == CMD)
	// {
	// 	cmd = (t_cmd *) tree;
	// 	if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
	// 		ft_cd(tree);
	// }
	if (fd == -1)
	{
		id = fork();
		if (id == -1)
			exit(1);
		else if (id == 0)
			exec_tree(tree, fd, envp);
		wait(&status);
	}
	else
		exec_tree(tree, fd, envp);
}
