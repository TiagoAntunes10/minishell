/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/20 21:28:23 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	cmd_dist(t_tree *tree)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) tree;
	if (ft_strncmp(cmd->cmd, "$", ft_strlen(cmd->cmd)))
		dollar_sub(cmd, 0);
	if (ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)))
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)))
		ft_pwd(fd);
	else if (ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)))
		ft_export(cmd);
	else if (ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)))
		ft_unset(cmd);
	else if (ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)))
		ft_env(cmd);
	// TODO: The exit function will not be able to free the whole tree
	else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)))
		exit_success((t_tree *) cmd, 0);
	else
		std_cmd(cmd);
}

static void	exec_tree(t_tree *tree, int fd)
{
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		exec_pipe(tree, fd);
	else if (tree->type == DELIM)
		exec_delim(tree, fd);	
	else if (tree->type == REDIR)
		exec_redir(tree, fd);
	else if (tree->type == CMD)
		cmd_dist(tree, fd);
}

// TODO: Handle input redirection with ';' and cd
void	execution(t_tree *tree, int fd)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
			ft_cd(tree);
	}
	exec_tree(tree, fd);
}
