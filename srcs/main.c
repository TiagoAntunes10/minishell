/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/31 18:21:23 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	execution(t_tokens token_lst, char **envp)
{
	int pid;
	int	status;

	if (is_builtin(token_lst[0]))
		return (builtin(token_lst[0], token_lst));
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


//TODO: Verify if fd 1 is a terminal (that should be the standard)
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*input;
	char		prompt[4096] = {0};
	t_tokens	*tokens_lst;

	input = readline(prompt);
	//while (check_end() != 0)
	while (input)
	{
		add_history(input);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		if (input != NULL)
		{
			tokens_lst = tokenization(input);
			free(input);
			execution(tokens_lst, envp);
			clear_lst(tokens_lst);
		}
		input = readline(prompt);
	}
}
