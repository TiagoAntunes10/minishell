/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:48:30 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/09 14:50:35 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

#endif
