/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/24 15:35:38 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	get_full_str(t_cmd *cmd, t_envp *envp, int is_bt)
{
	int		i;

	i = 0;
	quotes_pairs(cmd->cmd, envp, is_bt, 1);
	cmd->cmd = remove_quotes(cmd->cmd, envp);
	while (cmd->opt[i] != NULL)
	{
		if (quotes_pairs(cmd->opt[i], envp, is_bt, 0) == -1)
			return (-1);
		cmd->opt[i] = remove_quotes(cmd->opt[i], envp);
		i++;
	}
	return (0);
}

static int	cmd_dist(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) tree;
	if (get_full_str(cmd, envp, 1) == -1)
		return (1);
	if (ft_strncmp(cmd->cmd, "echo", lencmp(cmd->cmd, "echo")) == 0)
		return (ft_echo(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "pwd", lencmp(cmd->cmd, "pwd")) == 0)
		return (ft_pwd(), 1);
	else if (ft_strncmp(cmd->cmd, "export", lencmp(cmd->cmd, "export")) == 0)
		return (ft_export(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "unset", lencmp(cmd->cmd, "unset")) == 0)
		return (ft_unset(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "env", lencmp(cmd->cmd, "env")) == 0)
		return (ft_env(cmd, envp), 1);
	else if (ft_strncmp(cmd->cmd, "cd", lencmp(cmd->cmd, "cd")) == 0)
		return (ft_cd(cmd, envp), 1);
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

	status = 0;
	if (fd == -1)
	{
		signal_decider(tree);
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
		else if (ft_strncmp(cmd->cmd, "exit", lencmp(cmd->cmd, "exit")) == 0)
			ft_exit((t_tree *)cmd, envp);
		else
			child_exec(tree, fd, envp);
	}
	else
		child_exec(tree, fd, envp);
}
