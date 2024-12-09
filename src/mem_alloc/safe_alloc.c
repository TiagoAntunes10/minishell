/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:12:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/28 21:22:18 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Think how this should be applied because of the error handling
void	*safe_alloc(unsigned int size, unsigned int type,
					t_tree *tree, t_envp *envp)
{
	void	*var;

	var = malloc(size * type);
	if (var == NULL)
		exit_failure(tree, -1, envp);
	ft_bzero(var, size * type);
	return (var);
}
