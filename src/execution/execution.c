/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:26:12 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/05 14:47:14 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: Get mininal builtin recognition for exec and path testing
//TODO: Macro WIFEXITED and WEXITSTATUS need a struct to save the status for $?
//TODO: use STAT function struct to check metadata of files for possible erros

int	is_builtin(t_tokens token_lst[0])
{
	auto char *builtins[] = {"exit", "cd", NULL};
	int	i;

	i = -1;
	while (builtins[++i])
		if (token_lst[0] && !ft_strcmp(builtins[i], token_lst[0]))
			return (1);
	return (0);
}

int	execution(t_tokens token_lst, char **envp)
{
	int pid;
	int	status;

	if (is_builtin(token_lst[0]))
		return (builtin(token_lst[0], token_lst));
	signal_child();
	pid = fork();
	if (-1 == pid)
		return (temp_err("ERROR\n"), 1);
	if (!pid)
	{
		execve(ft_path(token_lst[0]), token_lst, envp);
		temp_err("ERROR\n");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}
