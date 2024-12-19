/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:11:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/18 22:07:34 by tialbert         ###   ########.fr       */
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
char			*conc_str(char *s1, char *s2, char *s3, t_envp *envp);

#endif
