/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:50:36 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/10 14:28:04 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	stat_ret(char *msg, int ex_code)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	g_exit_code = ex_code;
	return (ex_code);
}

static int	ft_isspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' || (str[i] < 9 && str[i] > 13))
			return (0);
	return (1);
}

int	to_skip_or_not_to_skip(char **input, t_envp *envp)
{
	if (!ft_strncmp(*input, "$", lencmp(*input, "$")))
		return (0);
	else if (!ft_strncmp(*input, "$?", lencmp(*input, "$?")))
		return (0);
	else if (**input == '$' && (!search_envp(envp, *input + 1)
		|| ft_isspace(search_envp(envp, *input + 1)->value)))
		return (1);
	return (0);
}
