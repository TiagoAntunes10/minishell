/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:55 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/13 22:41:15 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLER_H
# define SIGHANDLER_H

# include <signal.h>
# include "tree.h"

//signal receivers

void	signal_parent(void);
void	signal_child(void);
void	signal_ignore(void);
void	signal_heredoc(void);
void	signal_grand(void);

//signal handlers

void	handle_parent(int signum);
void	handle_child(int signum);
void	handle_heredoc(int signum);
void	signal_decider(t_tree *tree);
void	handle_grandchild(int signum);

#endif
