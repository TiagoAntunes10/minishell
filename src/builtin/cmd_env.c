/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:58:19 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/18 17:19:35 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//TODO: ERROR for too many args? is it really necessary?
//TODO: should just use printf maybe?


/*int	ft_env(t_cmd *cmd, t_envp *envp)
{
	while (envp)
	{
		ft_putstr_fd(envp->key, STDOUT_FILENO);
		ft_putchar_fd(61, STDOUT_FILENO);
		ft_putstr_fd(envp->value, STDOUT_FILENO);
		ft_putchar_fd(10, STDOUT_FILENO);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}*/

//env in bash does not print evs with NULL as value, export will

int	ft_env(t_cmd *cmd, t_envp *envp)
{
	while (envp)
	{
		if (envp->value)
			printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
