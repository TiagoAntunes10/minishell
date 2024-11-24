/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:45:27 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/24 17:48:29 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_envp	*search_envp(t_envp *envp, char *var)
{
	while (ft_strncmp(envp->key, var, ft_strlen(var)) != 0)
		envp = envp->next;
	return (envp);
}
