/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:06:26 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/14 21:06:54 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: handle -nnnnnnn?
//TODO: check how echo handles new lines withing an argument

int	ft_echo(t_cmd *cmd, t_envp *envp)
{
	(void)envp;
	int	i;
	int nflag;

	i = 1;
	nflag = 0;
	if ((cmd->opt[1]) && !ft_strncmp(cmd->opt[1], "-n", 2))
	{
		nflag = 1;
		i++;
	}
	i--;
	while (cmd->opt[++i])
	{
		ft_putstr_fd(cmd->opt[i], STDOUT_FILENO);
		if (cmd->opt[i] && cmd->opt[i + 1])
			ft_putchar_fd(32, STDOUT_FILENO);	
	}
	if (!nflag)
		ft_putchar_fd(10, STDOUT_FILENO);	
	return (EXIT_SUCCESS);
}
