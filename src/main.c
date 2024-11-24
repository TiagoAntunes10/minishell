/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/11/13 22:19:42 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/13 22:20:28 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/19 21:39:48 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

//TODO: Verify if fd 1 is a terminal (that should be the standard)
>>>>>>> 91d655cd368eec5976dfca42dd733e0176863e75
//TODO: Check if this is the best way to have access to the envirenment variables
//TODO: cd must execute in the parent process (it does not work with pipes and ';'), all other cmds execute in child processes
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tree	*tree;

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
			execution(tokens_lst, envp);
			clear_lst(tokens_lst);
			execution(tree, -1);
			clear_tree(tree);
		}
		input = readline(prompt);
	}
}
