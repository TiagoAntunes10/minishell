/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:27:18 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/15 18:03:55 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
//NOTE: signal child needs to be called before forking, and signal parent
//needs to be restored after the waitpid;
//TODO: heredoc signal handling?

extern int	g_exit_code;

void	handle_parent(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	handle_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: (core dumped)\n", STDERR_FILENO);
	g_exit_code = 128 + signum;
}

void	handle_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_code = 130;
	exit(g_exit_code);
}

void	signal_decider(t_tree *tree)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)tree;
	if (tree->type == DELIM)
		signal_ignore();
	else if (tree->type == CMD
		&& !ft_strncmp(cmd->cmd, "./minishell",
			lencmp(cmd->cmd, "./minishell")))
		signal_ignore();
	else
		signal_child();
}
