/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/15 22:01:44 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static unsigned int	lencmp(char *s1, char *s2)
{
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}

static int	cmd_dist(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) tree;
	// check_dolla(cmd, envp);
	if (ft_strncmp(cmd->cmd, "echo", lencmp(cmd->cmd, "echo")) == 0)
		return (g_exit_code = ft_echo(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "pwd", lencmp(cmd->cmd, "pwd")) == 0)
		return (g_exit_code = ft_pwd(), 1);
	else if (ft_strncmp(cmd->cmd, "export", lencmp(cmd->cmd, "export")) == 0)
		return (g_exit_code = ft_export(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "unset", lencmp(cmd->cmd, "unset")) == 0)
		return (g_exit_code = ft_unset(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "env", lencmp(cmd->cmd, "env")) == 0)
		return (g_exit_code = ft_env(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
		return (g_exit_code = ft_cd(cmd, envp), 1);
	return (0);
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
		std_cmd((t_cmd *)tree, envp);
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
	if (tree == NULL)
	{
		clear_tree(tree);
		return ;
	}
	if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (cmd_dist(tree, envp) == 1)
			return ;
		else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
			exit_success((t_tree *) cmd, -1, envp);
		else
			child_exec(tree, fd, envp);
	}
	else
		child_exec(tree, fd, envp);
}
