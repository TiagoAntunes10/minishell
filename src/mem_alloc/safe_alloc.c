/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:12:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/13 18:39:44 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	*safe_alloc(unsigned int size, unsigned int type,
					t_tree *tree, t_envp *envp)
{
	void	*var;

	var = malloc(size * type);
	if (var == NULL)
		exit_failure(tree, NULL, envp);
	ft_bzero(var, size * type);
	return (var);
}

void	*split_alloc(unsigned int size, unsigned int type,
					char **arr, t_envp *envp)
{
	void	*var;

	var = malloc(size * type);
	if (var == NULL)
	{
		clear_arr(arr);
		exit_failure(NULL, NULL, envp);
	}
	ft_bzero(var, size * type);
	return (var);
}
