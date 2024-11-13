/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
<<<<<<<< HEAD:srcs/main.c
/*   Updated: 2024/11/05 14:26:04 by rapcampo         ###   ########.fr       */
========
/*   Updated: 2024/11/08 21:42:42 by tialbert         ###   ########.fr       */
>>>>>>>> 71ce289d75c5a9ae06a9d8fa17370ae53fa319ee:src/main.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Verify if fd 1 is a terminal (that should be the standard)
<<<<<<<< HEAD:srcs/main.c
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*input;
	char		prompt[4096] = {0};
	struct t_tokens	*tokens_lst;
========
//TODO: Check if this is the best way to have access to the envirenment variables
//TODO: cd must execute in the parent process (it does not work with pipes and ';'), all other cmds execute in child processes
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tree	*tree;
>>>>>>>> 71ce289d75c5a9ae06a9d8fa17370ae53fa319ee:src/main.c

	input = readline(prompt);
	//while (check_end() != 0)
	while (input)
	{
		add_history(input);
		signal_parent();
		if (input != NULL)
		{
			tree = tokenisation(input);
			free(input);
<<<<<<<< HEAD:srcs/main.c
			execution(tokens_lst, envp);
			clear_lst(tokens_lst);
========
			execution(tree, -1);
			clear_tree(tree);
>>>>>>>> 71ce289d75c5a9ae06a9d8fa17370ae53fa319ee:src/main.c
		}
		input = readline(prompt);
	}
}
