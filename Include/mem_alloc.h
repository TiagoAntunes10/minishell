/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:24:11 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/13 18:40:09 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_ALLOC_H
# define MEM_ALLOC_H

# include "envp.h"
# include "tree.h"


/* ************************************************************************** */
/*                            MEM ALLOCATION                                  */
/* ************************************************************************** */
void	*safe_alloc(unsigned int size, unsigned int type,
					t_tree *tree, t_envp *envp);
void	*split_alloc(unsigned int size, unsigned int type,
					char **arr, t_envp *envp);

#endif
