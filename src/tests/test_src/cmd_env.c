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

#include "macro.h"

//TODO: ERROR for too many args? is it really necessary?
//TODO: should just use printf maybe?


/*int	ft_env(t_cmd *cmd, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	while (head)
	{
		ft_putstr_fd(head->key, STDOUT_FILENO);
		ft_putchar_fd(61, STDOUT_FILENO);
		ft_putstr_fd(head->value, STDOUT_FILENO);
		ft_putchar_fd(10, STDOUT_FILENO);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}*/

//env in bash does not print envs with NULL as value, export will

int	ft_env(t_cmd *cmd, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
