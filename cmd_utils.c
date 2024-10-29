/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:08:21 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/20 18:03:21 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	dollar_sub(t_tokens *token_lst, int type)
{
	char	*env;

	if (type == 0)
	{
		env = getenv(token_lst->cmd + 1);
		free(token_lst->cmd);
		if (env != NULL)
		{
			token_lst->cmd = malloc(ft_strlen(env) + 1);
			if (token_lst->cmd == NULL)
				exit_failure(token_lst, 0);
			ft_strlcpy(token_lst->cmd, env, ft_strlen(env));
		}
		free(env);
	}
	env = getenv(token_lst->options[type] + 1);
	free(token_lst->options[type]);
	if (env != NULL)
	{
		token_lst->options[type] = malloc(ft_strlen(env) + 1);
		if (token_lst->options[type] == NULL)
			exit_failure(token_lst, 0);
		ft_strlcpy(token_lst->options[type], env, ft_strlen(env));
	}
	free(env);
}
