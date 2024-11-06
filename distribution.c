/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/06 21:48:07 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	cmd_dist(t_tokens *token_lst, int *pipe)
{
	char	*cmd;

	cmd = token_lst->cmd;
	if (ft_strncmp(cmd, "$", 1))
		dollar_sub(token_lst, 0);
	if (ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		ft_echo(token_lst, pipe);
	else if (ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		ft_cd(token_lst);
	else if (ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		ft_pwd(pipe);
	else if (ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		ft_export(token_lst, pipe);
	else if (ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		ft_unset(token_lst, pipe);
	else if (ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		ft_env(token_lst, pipe);
	else if (ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		exit_success(token_lst, 0);
	else
		std_cmd(token_lst, pipe);
}

static void	exec_tree(t_tree *tree)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		exec_pipe(tree);
	else if (tree->type == DELIM)
		exec_delim(tree);	
	else if (tree->type == LIST)
		exec_list(tree);
	else if (tree->type == REDIR)
		exec_redir(tree);
	else if (tree->type == CMD)
		cmd_dist(tree);
}

// TODO: Handle input redirection with ';' and cd
void	execution(t_tree *tree)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
			ft_cd(tree);
	}
	exec_tree(tree);
}
