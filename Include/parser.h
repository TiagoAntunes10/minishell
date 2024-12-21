/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:48:30 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/21 15:49:18 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "envp.h"
# include "tree.h"

/* ************************************************************************** */
/*                            TOKEN CREATION                                  */
/* ************************************************************************** */

t_tree			*tokenisation(char *input, t_envp *envp);
t_tree			*token_dist(t_tree *tree, t_envp *envp, char **input);
int				count_opt(char **tokens);
t_tree			*cmd_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*delim_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*pipe_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*redir_node(t_tree *tree, char **input, int mode, t_envp *envp);
t_tree			*org_tree(t_tree *tree, t_tree *cmd);

/* ************************************************************************** */
/*                            TOKEN UTILS                                     */
/* ************************************************************************** */

int				count_words(char *str);
unsigned int	mod_strlen(char *str);
char			**split_input(char *str, t_envp *envp);
void			check_outfile(char *input, int mode,
					t_tree *tree, t_envp *envp);

#endif
