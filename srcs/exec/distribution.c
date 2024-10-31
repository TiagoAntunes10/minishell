/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/20 18:04:50 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_dist(t_tokens *token_lst, int *pipe)
{
	char	*cmd;

	cmd = token_lst->cmd;
	if (ft_strncmp(cmd, "$", 1))
		dollar_sub(token_lst, 0);
	if (ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		ft_echo(token_lst, pipe);
	else if (ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		ft_cd(token_lst);
	else if (ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		ft_pwd(pipe);
	else if (ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		ft_export(token_lst, pipe);
	else if (ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		ft_unset(token_lst, pipe);
	else if (ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		ft_env(token_lst, pipe);
	else if (ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		exit_success(token_lst, 0);
	else
		std_cmd(token_lst, pipe);
}

void	execution(t_tokens *tokens_lst)
{
	int			lst_size;

	lst_size = lst_len(tokens_lst);
	if (lst_size == 1)
		cmd_dist(tokens_lst, NULL);
	else
		fork_init(tokens_lst, lst_size);
}
