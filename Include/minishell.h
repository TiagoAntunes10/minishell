/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:54 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/09 22:25:06 by tialbert         ###   ########.fr       */
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
# include "envp.h"
# include "mem_alloc.h"
# include "utils.h"
# include "execution.h"
# include "sighandler.h"
# include "macro.h"

# define PIPE	1
# define DELIM	2
# define CMD	3
# define REDIR	4

extern int	g_exit_code;

/* ************************************************************************** */
/*                            EXECUTION                                       */
/* ************************************************************************** */

void	execution(t_tree *tree, int fd, t_envp *envp);
void	exec_pipe(t_tree *tree, int fd, t_envp *envp);
void	child_pipe(t_pipe *pipe_node, t_envp *envp, int *inp_pipe);
void	pipe_in_pipe(int *inp_pipe, int fd, t_envp *envp);
void	exec_delim(t_tree *tree, t_envp *envp);
void	exec_list(t_tree *tree, int fd, t_envp *envp);
void	exec_redir(t_tree *tree, t_envp *envp);
void	redir_read(t_redir *redir, t_envp *envp);
void	redir_write(t_redir *redir, t_envp *envp);
void	std_cmd(t_cmd *cmd, t_envp *envp);
int		count_child(int start, int ope);
void	child_wait(t_envp *envp);
void	exec_wait(pid_t id);

/* ************************************************************************** */
/*                            EXPANDER                                        */
/* ************************************************************************** */

int		get_full_str(t_cmd *cmd, t_envp *envp, int is_bt);
void	check_dolla(char **origin, t_envp *envp, int here_doc);
int		quotes_pairs(char *str, t_envp *envp, int is_bt);
char	*clean_str(char *origin, t_envp *envp, int here_doc);

#endif
