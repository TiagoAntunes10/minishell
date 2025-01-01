/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:51:45 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/15 17:55:59 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_pwd(t_cmd *cmd, t_envp *envp)
{
	char	*cwd;

	((void)cmd, (void)envp);
	cwd = getcwd(NULL, 4096);
	if (printf("%s\n", cwd) < 0)
	{
		free(cwd);
		return (stat_ret(RED PWD_NO_PRNT RST, 126));
	}
	if (cwd)
		free(cwd);
	return (stat_ret(NULL, 0));
}
