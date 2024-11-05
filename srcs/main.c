/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/05 14:26:04 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>




//TODO: Verify if fd 1 is a terminal (that should be the standard)
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*input;
	char		prompt[4096] = {0};
	struct t_tokens	*tokens_lst;

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
