/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/14 23:09:03 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

// TODO: Update SHLEVEL environmental variable
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tree	*tree;
	t_envp	*envp_lst;
	char	prompt[7000000] = {RED "testshell->" RST};

	(void) argc;
	(void) argv;
	envp_lst = arr_to_lst(env);
	input = readline(prompt);
	while (input)
	{
		signal_parent();
		add_history(input);
		tree = tokenisation(input, envp_lst);
		free(input);
		execution(tree, -1, envp_lst);
		clear_tree(tree);
		input = readline(prompt);
	}
	rl_clear_history();
	clear_envp(envp_lst);
}
