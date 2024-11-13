/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:51:07 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/09 14:51:53 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

/* ************************************************************************** */
/*                            CLEANUP                                         */
/* ************************************************************************** */

char			**clear_arr(char **arr);
void			clear_tree(t_tree *tree);
void			exit_success(t_tree *tree, int fd);
void			exit_failure(t_tree *tree, int fd);

#endif
