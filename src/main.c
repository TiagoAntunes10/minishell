/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:19:42 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/13 22:20:28 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

g_exit_code;
//TODO: Verify if fd 1 is a terminal (that should be the standard)
//TODO: Check if this is the best way to have access to the envirenment variables
//TODO: cd must execute in the parent process (it does not work with pipes and ';'), all other cmds execute in child processes
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tree	*tree;
	t_envp	*envp_lst;

	input = readline(prompt);
	(void) argc;
	(void) argv;
	envp_lst = arr_to_lst(env);
	while (input)
	{
		add_history(input);
		signal_parent();
		tree = tokenisation(input);
		free(input);
		execution(tree, -1);
		execution(tree, -1, envp_lst);
		clear_tree(tree);
		input = readline(prompt);
	}
}
