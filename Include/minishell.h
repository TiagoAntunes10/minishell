/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:54 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/24 16:04:28 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/ft_printf.h"
# include "tree.h"
# include "parser.h"
# include "cleanup.h"
# include "macro.h"
# include "execution.h"

# define PIPE	1
# define LIST	2
# define DELIM	3
# define CMD	4
# define REDIR	5
# include "./tree.h"
# include "./parser.h"
# include "./cleanup.h"
# include "./envp.h"

# define PIPE	1
# define DELIM	2
# define CMD	3
# define REDIR	4

/* ************************************************************************** */
/*                            EXECUTION                                       */
/* ************************************************************************** */

void	execution(t_tree *tree, int fd, t_envp *envp);
void	exec_pipe(t_tree *tree, int fd, t_envp *envp);
void	exec_delim(t_tree *tree, int fd, t_envp *envp);
void	exec_list(t_tree *tree, int fd, t_envp *envp);
void	exec_redir(t_tree *tree, int fd, t_envp *envp);
void	std_cmd(t_cmd *cmd, t_envp *envp);
// void			ft_echo(t_tokens *token_lst, int *pipe);
// void			ft_pwd(int *pipe);
// void			ft_cd(t_tokens *token_lst);

/* ************************************************************************** */
/*                            CMD UTILS                                       */
/* ************************************************************************** */
// void			dollar_sub(t_tokens *token_lst, int type);

#endif
