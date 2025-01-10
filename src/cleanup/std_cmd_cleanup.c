/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:20:14 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 14:21:25 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	clear_std_cmd(t_envp *envp, char *cmd_path, char **envp_arr)
{
	if (envp->r_pipe != -1)
		close(envp->r_pipe);
	if (envp->w_pipe != -1)
		close(envp->w_pipe);
	if (cmd_path)
		free(cmd_path);
	clear_arr(envp_arr);
}
