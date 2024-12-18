/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/18 20:48:32 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static void	cmd_dist(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	if (ft_strncmp(cmd->cmd, "echo", lencmp(cmd->cmd, "echo")) == 0)
		ft_echo(cmd, envp);
	else if (ft_strncmp(cmd->cmd, "pwd", lencmp(cmd->cmd, "pwd")) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", lencmp(cmd->cmd, "export")) == 0)
		ft_export(cmd, envp);
	else if (ft_strncmp(cmd->cmd, "unset", lencmp(cmd->cmd, "unset")) == 0)
		ft_unset(cmd, envp);
	else if (ft_strncmp(cmd->cmd, "env", lencmp(cmd->cmd, "env")) == 0)
		ft_env(cmd, envp);
	else
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

static void	child_exec(t_tree *tree, int fd, t_envp *envp)
{	
	int	id;
	int	status;

	if (fd == -1)
	{
		signal_child();
		id = fork();
		if (id == -1)
			exit_failure(tree, NULL, envp);
		else if (id == 0)
			exec_tree(tree, fd, envp);
		wait(&status);
	}
	else
	{
		exec_tree(tree, fd, envp);
		exit_success(envp->root, fd, envp);
	}
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	signal_parent();
}

void	execution(t_tree *tree, int fd, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
			ft_cd(cmd, envp);
		else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
			exit_success((t_tree *) cmd, -1, envp);
		else
			child_exec(tree, fd, envp);
	}
	else
		child_exec(tree, fd, envp);
}
