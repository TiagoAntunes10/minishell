/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:08:53 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/30 17:10:35 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	save_root(t_envp *envp, t_tree *root)
{
	while (envp != NULL)
	{
		envp->root = root;
		envp = envp->next;
	}
}
