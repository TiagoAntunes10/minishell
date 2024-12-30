/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/21 15:47:00 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	g_exit_code = 0;

static char	*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 4096);
	if (!pwd)
		return (LOWER_PROMPT);
	tmp = ft_calloc(1,
			(ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, pwd, ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2);
	prompt = ft_strjoin(tmp, "\n"LOWER_PROMPT);
	free(tmp);
	free(pwd);
	return (prompt);
}

static void	input_reader(t_envp *envp)
{
	t_tree	*tree;
	char	*input;
	char	*prompt;

	prompt = get_prompt();
	input = readline(prompt);
	while (1)
	{
		if (!input)
		{
			free(prompt);
			return ;
		}
		add_history(input);
		tree = tokenisation(input, envp);
		save_root(envp, tree);
		free(input);
		free(prompt);
		execution(tree, -1, envp);
		clear_tree(tree);
		prompt = get_prompt();
		input = readline(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envp	*envp_lst;

	((void)argc, (void)argv);
	envp_lst = arr_to_lst(env);
	signal_parent();
	update_shlvl(envp_lst);
	input_reader(envp_lst);
	rl_clear_history();
	clear_envp(envp_lst);
	printf("exit\n");
	return (g_exit_code);
}
