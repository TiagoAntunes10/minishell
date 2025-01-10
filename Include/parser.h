/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:48:30 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 17:09:15 by tialbert         ###   ########.fr       */
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
char			**ignore_redir(char ***input, char **input_cpy);
char			**ignore_opt(char **input);
int				count_opt(char **tokens);
t_tree			*cmd_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*delim_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*pipe_node(t_tree *tree, char **input, t_envp *envp);
t_tree			*redir_node(t_tree *tree, char **input, int mode, t_envp *envp);
void			org_tree(t_tree *tree, t_tree *cmd);
t_tree			*org_redir_read(t_redir *redir, t_tree *tree);

/* ************************************************************************** */
/*                            TOKEN UTILS                                     */
/* ************************************************************************** */

int				count_words(char *str);
unsigned int	check_quotes(char **str, int len);
unsigned int	mod_strlen(char *str);
char			**split_input(char *str, t_envp *envp);
t_tree			*org_delim(t_delim *delim, t_tree *tree);
void			check_outfile(t_redir *redir, int mode, t_envp *envp);
void			tree_leafs_pipe(t_tree *tree, t_pipe *pipe);
int				check_cmd(t_tree *tree);
void			tree_leafs_redir(t_tree *tree, t_redir *redir);
int				is_redir_valid(char *file);

#endif
