/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:58:08 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/19 16:53:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	end_heredoc(t_envp *envp, int inp_pipe, t_tree *tree, t_delim *delim)
{
	static t_envp	*env;
	static int		pipes;
	static t_tree	*tree_cpy;
	static t_delim	*delim_cpy;

	if (envp)
		env = envp;
	if (inp_pipe != -1)
		pipes = inp_pipe;
	if (tree)
		tree_cpy = tree;
	if (delim)
		delim_cpy = delim;
	if (inp_pipe == -1)
	{
		free(delim_cpy->delim);
		free(delim_cpy);
		close(pipes);
		clear_tree(tree_cpy);
		exit_failure(NULL, NULL, env);
	}
}
