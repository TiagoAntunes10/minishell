/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:03:38 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/16 15:41:34 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	signal_parent(void)
{
	signal(SIGINT, handle_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_grand(void)
{
	// signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, handle_grandchild);
	signal(SIGQUIT, handle_grandchild);
}

void	signal_child(void)
{
	// signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
}

void	signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
