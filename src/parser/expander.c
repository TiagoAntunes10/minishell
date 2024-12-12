/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:44:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/11 23:15:07 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: check if replacing cmd->cmd instead of opt is the best way to do this
extern int	g_exit_code;

void	expand_variable(t_cmd *cmd, t_envp *envp)
{
	char	*value;
	char	*key;

	key = ft_strdup(cmd->cmd + 1);
	if (!ft_strncmp(cmd->cmd, "$?", ft_strlen(cmd->cmd)))
		value = ft_itoa(g_exit_code);
	else
		value = ft_strdup(search_envp(envp, key)->value);
	ft_free(cmd->cmd);
	cmd->cmd = value;
	ft_free(key);
}
