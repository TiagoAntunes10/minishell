/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:11:03 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 15:33:50 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "tree.h"
# include "envp.h"

/* ************************************************************************** */
/*                               UTILS                                        */
/* ************************************************************************** */
void			save_root(t_envp *envp, t_tree *root);
unsigned int	lencmp(char *s1, char *s2);
int				stat_ret(char *msg, int ex_code);
char			*conc_str(char **str_arr, t_envp *envp);
char			**str_divide(char *str, t_envp *envp, int pos);
int				is_valid_identifier(char *keyvalue);
int				redir_check(char *input);
void			remove_quotes(char **arr, int here_doc, t_envp *envp);
#endif
