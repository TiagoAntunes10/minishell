/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:21:01 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/10 15:31:40 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int g_exit_code;

int	ft_exit(t_tree *tree, t_envp *envp)
{
	if (envp != NULL)
		clear_envp(envp);
	if (tree != NULL)
		clear_tree(tree);
	return (g_exit_code);
}
