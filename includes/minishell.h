/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:54 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/31 23:18:09 by rapcampo         ###   ########.fr       */
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
# include <signal.h>
# include "macro.h"
# include "libft.h"
# include "execution.h"

typedef struct s_tokens {
	char			*infile;
	char			*cmd;
	char			**options;
	char			*outfile;
	int				priority;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}				t_tokens;

/* ************************************************************************** */
/*                            LIST OPERATIONS                                 */
/* ************************************************************************** */

t_tokens		*create_lst(char **tokens);
int				lst_len(t_tokens *lst);

/* ************************************************************************** */
/*                            TOKEN CREATION                                  */
/* ************************************************************************** */

t_tokens		*tokenisation(char *input);

/* ************************************************************************** */
/*                            TOKEN UTILS                                     */
/* ************************************************************************** */

int				count_words(char *str);
unsigned int	mod_strlen(char *str);
char			**split_input(char *str);


/* ************************************************************************** */
/*                            CLEANUP                                         */
/* ************************************************************************** */
char			**clear_arr(char **arr);
t_tokens		*clear_lst(t_tokens *tokens);
void			exit_success(t_tokens *tokens, int fd);
void			exit_failure(t_tokens *tokens, int fd);

/* ************************************************************************** */
/*                            FT_CMDS                                         */
/* ************************************************************************** */
void			ft_echo(t_tokens *token_lst, int *pipe);
void			ft_pwd(int *pipe);
void			ft_cd(t_tokens *token_lst);
//placeholder
void			ft_env(t_tokens *token_lst, int *pipe);
void			ft_unset(t_tokens *token_lst, int *pipe);
void			ft_export(t_tokens *token_lst, int *pipe);

/* ************************************************************************** */
/*                            CMD UTILS                                       */
/* ************************************************************************** */
void			dollar_sub(t_tokens *token_lst, int type);

#endif
