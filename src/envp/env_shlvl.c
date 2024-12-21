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
#include <stdlib.h>

//TODO: update shlvl, value could be retrieved with getenv
//TODO: if retrieved with getenv, just use export
//TODO: if not, atoi and itoa needed for conversion of values
//TODO: should receive envp, should pass the tree too for export

void	update_shlvl(t_envp *envp)
{
	printf("%s", getenv("SHLVL"));
	export_env(getenv("SHLVL"), envp);
}
