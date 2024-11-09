/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:54 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/09 15:01:57 by tialbert         ###   ########.fr       */
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
# include "parser.h"
# include "cleanup.h"

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
/*                            EXECUTION                                       */
/* ************************************************************************** */

void			execution(t_tree *tree, int fd);
void			exec_pipe(t_tree *tree, int fd);
void			exec_delim(t_tree *tree, int fd);
void			exec_list(t_tree *tree, int fd);
void			exec_redir(t_tree *tree, int fd);
// void			ft_echo(t_tokens *token_lst, int *pipe);
// void			ft_pwd(int *pipe);
// void			ft_cd(t_tokens *token_lst);

/* ************************************************************************** */
/*                            CMD UTILS                                       */
/* ************************************************************************** */
// void			dollar_sub(t_tokens *token_lst, int type);

#endif
