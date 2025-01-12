/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:21:01 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/12 20:58:01 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: exit will call exit_success function for cleanup
//TODO: should check for extra arguments more than 1 should give an error
//TODO: extra arguments should not contain any alpha characters
//TODO: should stay within 255, for that bash calculates the exit_status % 256

static long	ft_atol(char *nptr)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			neg *= -1;
	}
	if (ft_strlen (nptr + i) > 19)
		return (stat_ret(RED"exit: numeric argument required\n"RST, 2));
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (nptr[i++] - '0') + (res * 10);
	res *= neg;
	if (res > 9223372036854775807 || res < -9223372036854775807)
		return (stat_ret(RED"exit: numeric argument required"RST, 2));
	return (res);
}

static int	arg_isnum(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
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
		stat_ret(RED EX_MANY_ARG RST, 1);
		return ;
	}
	else if (cmd->opt[1] && !arg_isnum(cmd->opt[1]))
	{
		stat_ret(RED EX_ALPHA_ERR RST, 2);
		exit_failure(envp->root, NULL, envp);
	}
	else if (cmd->opt[1] && arg_isnum(cmd->opt[1]))
		g_exit_code = ft_atol(cmd->opt[1]) % 256;
	if (tree == envp->root)
	{
		if (printf("exit\n") == -1)
			return ;
	}
	if (envp->w_pipe == -1 && envp->r_pipe == -1)
		exit_success(envp->root, -1, envp);
}
