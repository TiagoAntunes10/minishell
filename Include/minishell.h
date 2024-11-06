/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:54 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/06 21:10:35 by tialbert         ###   ########.fr       */
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
# include "../libft/ft_printf.h"

# define PIPE	1
# define LIST	2
# define DELIM	3
# define CMD	4
# define REDIR	5

typedef struct s_tree {
	int	type;
}				t_tree;

typedef struct s_pipe {
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_pipe;

typedef struct s_lst {
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_lst;

typedef struct s_delim {
	int				type;
	char			*delim;
	struct s_tree	*right;
}				t_delim;

typedef struct s_cmd {
	int		type;
	char	*cmd;
	char	**opt;
}				t_cmd;

typedef struct s_redir {
	int				type;
	char			*file;
	int				mode;
	struct s_tree	*right;
}				t_redir;

/* ************************************************************************** */
/*                            LIST OPERATIONS                                 */
/* ************************************************************************** */

// t_tokens		*create_lst(char **tokens);
// int				lst_len(t_tokens *lst);

/* ************************************************************************** */
/*                            TOKEN CREATION                                  */
/* ************************************************************************** */

t_tree			*tokenisation(char *input);
int				count_opt(char **tokens);
t_tree			*cmd_node(t_tree *tree, char ***input);
t_tree			*delim_node(t_tree *tree, char ***input);
t_tree			*pipe_node(t_tree *tree);
t_tree			*lst_node(t_tree *tree);
t_tree			*redir_node(t_tree *tree, char ***input, int mode);
t_tree			*org_tree(t_tree *tree, t_tree *cmd);

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
void			clear_tree(t_tree *tree);
void			exit_success(t_tree *tree, int fd);
void			exit_failure(t_tree *tree, int fd);

/* ************************************************************************** */
/*                            EXECUTION                                       */
/* ************************************************************************** */

void			execution(t_tree *tree);
// void			ft_echo(t_tokens *token_lst, int *pipe);
// void			ft_pwd(int *pipe);
// void			ft_cd(t_tokens *token_lst);

/* ************************************************************************** */
/*                            CMD UTILS                                       */
/* ************************************************************************** */
// void			dollar_sub(t_tokens *token_lst, int type);

#endif
