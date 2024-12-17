/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/15 18:36:02 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

// TODO: Update SHLEVEL environmental variable
int	g_exit_code;
//TODO: Verify if fd 1 is a terminal (that should be the standard)
//TODO: Check if this is the best way to have access to the envirenment variables
//TODO: cd must execute in the parent process (it does not work with pipes and ';'), all other cmds execute in child processes

static char	*get_prompt(t_envp *envp)
{
	char	*prompt;
	char	*pwd;
	char	*tmp;

	pwd = search_envp(envp, "PWD")->value;
	tmp = ft_calloc(1, 
			(ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, pwd, ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2);
	prompt = ft_strjoin(tmp, "\n"LOWER_PROMPT);
	free(tmp);
	return (prompt);
}

static void	input_reader(t_envp *envp)
{
	t_tree	*tree;
	char	*input;

	input = readline(get_prompt(envp));
	while (1)
	{
		if (!input)
			break ;	
		add_history(input);
		tree = tokenisation(input, envp);
		save_root(envp, tree);
		free(input);
		execution(tree, -1, envp);
		clear_tree(tree);
		input = readline(get_prompt(envp));
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_envp	*envp_lst;

	((void)argc, (void)argv);
	envp_lst = arr_to_lst(env);
	signal_parent();
	input_reader(envp_lst);
	clear_envp(envp_lst);
	return (EXIT_SUCCESS);
}
