/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:51:45 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/01 19:41:52 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_pwd(t_cmd *cmd, t_envp *envp)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 4096);
	if (!cwd && search_envp(envp, "PWD"))
	{
		printf("%s\n", search_envp(envp, "PWD")->value);
		return (stat_ret(NULL, 0));
	}
	else if (!cwd && !search_envp(envp, "PWD"))
		return (stat_ret(RED PWD_NO_SET RST, 1));
	if (printf("%s\n", cwd) < 0)
	{
		free(cwd);
		return (stat_ret(RED PWD_NO_PRNT RST, 1));
	}
	if (cwd)
		free(cwd);
	return (stat_ret(NULL, 0));
}
