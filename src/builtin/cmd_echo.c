/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:06:26 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/12 20:41:51 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	is_nflag_valid(char *opt_str)
{
	int	i;

	i = 0;
	if (opt_str[0] != '-')
		return (0);
	while (opt_str[++i])
		if (opt_str[i] != 'n')
			return (0);
	return (1);
}

static void	putchar_check(char c, int fd, t_envp *envp)
{
	if (ft_putchar_fd(c, fd) == -1)
		exit_failure(envp->root, NULL, envp);

}
int	ft_echo(t_cmd *cmd, t_envp *envp)
{
	int	i;
	int	nflag;

	(void)envp;
	i = 1;
	nflag = 0;
	if ((cmd->opt[1]) && is_nflag_valid(cmd->opt[1]))
	{
		nflag = 1;
		i++;
	}
	i--;
	while (cmd->opt[++i])
	{
		if (ft_putstr_fd(cmd->opt[i], STDOUT_FILENO) == -1)
			exit_failure(envp->root, NULL, envp);
		if (cmd->opt[i] && cmd->opt[i + 1])
			putchar_check(32, STDOUT_FILENO, envp);
	}
	if (!nflag)
		putchar_check(10, STDOUT_FILENO, envp);
	return (stat_ret(NULL, 0));
}
