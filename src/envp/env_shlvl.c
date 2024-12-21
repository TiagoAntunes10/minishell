/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:21:27 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/20 23:32:21 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	update_shlvl(t_envp *envp)
{
	int		shlvl;
	char	*envshlvl;
	char	*itoa_lvl;
	
	if (search_envp(envp, "SHLVL") && search_envp(envp, "SHLVL")->value)
	{
		shlvl = ft_atoi(search_envp(envp, "SHLVL")->value);
		itoa_lvl = ft_itoa(shlvl + 1);
		envshlvl = ft_strjoin("SHLVL=", itoa_lvl);
		export_env(envshlvl, envp);
		free(envshlvl);
		free(itoa_lvl);
	}
	else
		export_env("SHLVL=1", envp);
}
