/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:58:08 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/26 16:06:39 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	end_heredoc(t_envp *envp, int *inp_pipe, int endflag)
{
	static t_envp	*env;
	static int		*pipes;
	int				i;

	if (envp)
		env = envp;
	if (inp_pipe)
		pipes = inp_pipe;
	if (endflag)
	{
		clear_tree(env->root);
		clear_envp(env);
		i = 0;
		while (i < 2)
			close(pipes[i++]);
		exit(g_exit_code);
	}
}
