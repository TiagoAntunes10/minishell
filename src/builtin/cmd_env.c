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

int	ft_env(t_cmd *cmd, t_envp *envp)
{
	t_envp	*head;

	if (cmd->opt[1])
		return (stat_ret(RED ENV_NOFILE RST, 127));
	head = envp;
	while (head)
	{
		if (ft_strncmp(head->value, "", 1))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (stat_ret(NULL, 0));
}
