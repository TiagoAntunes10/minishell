/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:51:07 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/30 21:08:17 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "envp.h"
# include "tree.h"

/* ************************************************************************** */
/*                            CLEANUP                                         */
/* ************************************************************************** */

void	clean_cmd(t_tree *cmd, t_tree *tree, t_envp *envp);
void	clear_envp(t_envp *envp);
char	**clear_arr(char **arr);
void	clear_tree(t_tree *tree);
void	exit_success(t_tree *tree, int fd, t_envp *envp);
void	exit_failure(t_tree *tree, int *fd, t_envp *envp);
void	end_heredoc(t_envp *envp, int *inp_pipe, int endflag);

#endif
