/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/09 22:37:46 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	child_thrower(t_tree *tree, t_envp *envp)
{
	int		bt;
	t_cmd	*cmd;

	cmd = (t_cmd *)tree;
	bt = is_bt(cmd, envp);
	if (bt > 0)
		bt_exec(tree, envp, bt);
	else
		std_cmd((t_cmd *)tree, envp);
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
		child_thrower(tree, envp);
}

static void	child_exec(t_tree *tree, int fd, t_envp *envp)
{
	if (fd == -1)
	{
		signal_decider(tree);
		envp->id = fork();
		if (envp->id == -1)
			exit_failure(tree, NULL, envp);
		else if (envp->id == 0)
		{
			exec_tree(tree, fd, envp);
			exit_success(envp->root, fd, envp);
		}
		child_wait(envp);
	}
	else
	{
		exec_tree(tree, fd, envp);
		if (envp->id != 0)
			child_wait(envp);
		exit_success(envp->root, fd, envp);
	}
}

static void	cmd_tree_dist(t_tree *tree, int fd, t_envp *envp)
{
	t_cmd	*cmd;
	int		bt;

	cmd = (t_cmd *) tree;
	if (get_full_str(cmd, envp, 1) == -1)
		return ;
	bt = is_bt(cmd, envp);
	if (bt > 0 && fd == -1)
	{
		bt_exec(tree, envp, bt);
		return ;
	}
	else if (ft_strncmp(cmd->cmd, "exit", lencmp(cmd->cmd, "exit")) == 0)
		ft_exit((t_tree *)cmd, envp);
	child_exec(tree, fd, envp);
}

void	execution(t_tree *tree, int fd, t_envp *envp)
{
	if (tree == NULL)
		return ;
	if (tree->type == CMD)
		cmd_tree_dist(tree, fd, envp);
	else
		child_exec(tree, fd, envp);
}
