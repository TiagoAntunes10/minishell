/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/03 14:51:15 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	g_exit_code;

void	std_dup(t_envp *envp)
{
	envp->fd_in = dup(STDIN_FILENO);
	if (envp->fd_in == -1)
		exit_failure(NULL, NULL, envp);
	envp->fd_out = dup(STDOUT_FILENO);
	if (envp->fd_out == -1)
		exit_failure(NULL, NULL, envp);
}

void	reset_std(t_envp *envp)
{
	if (dup2(envp->fd_in, 0) == -1)
		exit_failure(NULL, NULL, envp);
	if (dup2(envp->fd_out, 1) == -1)
		exit_failure(NULL, NULL, envp);
}

void	clean_fd(t_envp *envp)
{
	close(envp->fd_in);
	close(envp->fd_out);
}

static char	*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 4096);
	if (!pwd && search_envp(envp, "PWD"))
		pwd = ft_strdup(search_envp(envp, "PWD")->value);
	else if (!pwd && !search_envp(envp, "PWD"))
		return (ft_strdup(LOWER_PROMPT));
	tmp = ft_calloc(1,
			(ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, pwd, ft_strlen(pwd) + ft_strlen(LOWER_PROMPT) + 2);
	prompt = ft_strjoin(tmp, "\n"LOWER_PROMPT);
	ft_free(tmp);
	ft_free(pwd);
	return (prompt);
}

static void	input_reader(t_envp *envp)
{
	t_tree	*tree;
	char	*input;
	char	*prompt;
	int		status;

	prompt = get_prompt(envp);
	input = readline(prompt);
	while (1)
	{
		if (!input)
		{
			ft_free(prompt);
			return ;
		}
		add_history(input);
		tree = tokenisation(input, envp);
		save_root(envp, tree);
		ft_free(input);
		ft_free(prompt);
		execution(tree, -1, envp);
		if (waitpid(envp->id, &status, 0) != -1)
		{
			envp->child_proc--;
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			signal_parent();
			envp->id = 0;
		}
		while (envp->child_proc)
		{
			wait(0);
			envp->child_proc--;
		}
		clear_tree(tree);
		reset_std(envp);
		prompt = get_prompt();
		input = readline(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envp	*envp_lst;

	((void)argc, (void)argv);
	envp_lst = arr_to_lst(env);
	std_dup(envp_lst);
	signal_parent();
	update_shlvl(envp_lst);
	input_reader(envp_lst);
	rl_clear_history();
	clean_fd(envp_lst);
	clear_envp(envp_lst);
	printf("exit\n");
	return (g_exit_code);
}
