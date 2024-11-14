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

#include "../../Include/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (cmd->opt)
		return (ft_putstr_fd("pwd: too many args", 2), 2);
	cwd = getcwd(NULL, 4096);
	if (printf("%s", cwd) < 0)
	{
		free(cwd);
		return (ft_putstr_fd("pwd: could not print directory", 2), 2);
	}
	if (cwd)
		free(cwd);
	return (0);
}
