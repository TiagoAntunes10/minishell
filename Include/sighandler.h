/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:55 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/06 15:51:00 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLER_H
# define SIGHANDLER_H

# include "minishell.h"
# include <signal.h>

//signal receivers

void	signal_parent(void);
void	signal_child(void);
void	signal_ignore(void);
//void	signal_heredoc(void);

//signal handlers

void	handle_parent(int signum);
void	handle_child(int signum);

#endif
