/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:27:18 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/08 11:31:45 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//NOTE: signal child needs to be called before forking, and signal parent
//needs to be restored after the waitpid;
//TODO: heredoc signal handling?

void	handle_parent(int signum)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 2);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: (core dumped)\n", 2);
	g_exit_status = 128 + signum;
}

