/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:51:45 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/14 21:06:06 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macro.h"

int	ft_pwd(t_cmd *cmd, t_envp *envp)
{
	(void)envp;
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	if (cmd->opt[1])
		return (free(cwd), ft_putstr_fd(RED PWD_ERR_ARG RST, 2), 2);
	if (printf("%s", cwd) < 0)
		return (free(cwd), ft_putstr_fd(RED PWD_NO_PRNT RST, 2), 2);
	if (cwd)
		free(cwd);
	return (0);
}
