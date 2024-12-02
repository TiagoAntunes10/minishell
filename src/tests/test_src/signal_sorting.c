/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:03:38 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/08 11:23:34 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macro.h"

//TODO: heredoc?


void	handle_parent(int signum)
{
	rl_replace_line("", 0);
	(void)!write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 2);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	signal_parent(void)
{
	signal(SIGINT, handle_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child(void)
{
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
