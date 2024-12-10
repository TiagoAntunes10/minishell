/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/06 15:40:33 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	g_exit_code;
//TODO: Verify if fd 1 is a terminal (that should be the standard)
//TODO: Check if this is the best way to have access to the envirenment variables
//TODO: cd must execute in the parent process (it does not work with pipes and ';'), all other cmds execute in child processes
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tree	*tree;
	t_envp	*envp_lst;

	((void) argc, (void) argv);
	envp_lst = arr_to_lst(env);
	input = readline(prompt);
	while (input)
	{
		add_history(input);
		signal_parent();
		tree = tokenisation(input);
		save_root(envp_lst, tree);
		free(input);
		execution(tree, -1, envp_lst);
		clear_tree(tree);
		input = readline(prompt);
	}
	rl_clear_history();
	clear_envp(envp_lst);
	ft_exit(1, 0);
}
