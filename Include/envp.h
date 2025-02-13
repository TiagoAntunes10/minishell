/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:58:51 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 09:37:00 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "tree.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	char			**input_arr;
	int				r_pipe;
	int				w_pipe;
	int				fd_in;
	int				fd_out;
	int				id;
	struct s_envp	*next;
	struct s_tree	*root;
}				t_envp;

/* ************************************************************************** */
/*                            ENVP_UTILS                                      */
/* ************************************************************************** */
char	**lst_to_arr(t_envp *envp);
t_envp	*arr_to_lst(char **envp);
char	**envp_split(char *str, t_envp *envp);

/* ************************************************************************** */
/*                            ENVP_SEARCH                                     */
/* ************************************************************************** */
t_envp	*search_envp(t_envp *envp, char *var);
void	update_shlvl(t_envp *envp);

#endif
