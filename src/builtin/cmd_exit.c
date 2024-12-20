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

extern int	g_exit_code;

//TODO: exit will call exit_success function for cleanup
//TODO: should check for extra arguments more than 1 should give an error
//TODO: extra arguments should not contain any alpha characters
//TODO: should stay within 255, for that bash calculates the exit_status % 256

static int	arg_isnum(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

void	ft_exit(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)tree;
	if (cmd->opt[1] && cmd->opt[2])
	{
		ft_putstr_fd(RED EX_MANY_ARG RST, STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	else if (cmd->opt[1] && !arg_isnum(cmd->opt[1]))
	{
		ft_putstr_fd(RED EX_ALPHA_ERR RST, STDERR_FILENO);
		g_exit_code = 2;
		exit_failure((t_tree *)cmd, NULL, envp);
	}
	else if (cmd->opt[1] && arg_isnum(cmd->opt[1]))
		g_exit_code = ft_atoi(cmd->opt[1]) % 256;
	printf("exit\n");
	exit_success((t_tree *)cmd, -1, envp);
}
