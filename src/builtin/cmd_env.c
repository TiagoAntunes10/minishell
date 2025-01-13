/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:58:19 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/12 20:56:36 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_env(t_cmd *cmd, t_envp *envp)
{
	t_envp	*head;

	if (cmd->opt[1])
		return (stat_ret(RED ENV_NOFILE RST, 127));
	head = envp->next;
	while (head)
	{
		if (ft_strncmp(head->value, "", 1))
		{
			if (printf("%s=%s\n", head->key, head->value) == -1)
				exit_failure(envp->root, NULL, envp);
		}
		head = head->next;
	}
	return (stat_ret(NULL, 0));
}
