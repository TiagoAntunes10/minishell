/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:26:12 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/05 14:47:14 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

char	ft_path(char *name)
{
	char	**path;
	int		i;
	struct stat	buffer = {0};

	path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path[++i])
	{
		char *tpath = ft_calloc(ft_strlen(path[i]) + ft_strlen(name) + 2, 1);
		if (!tpath)
			return (NULL);
		if (stat(tpath, &buffer) == 0)
		{
			ft_freematrix(path);
			return (tpath);
		}
		if (tpath)
		{
			free(tpath);
			tpath = NULL;
		}
	}
	ft_freematrix(path);
	return (ft_strdup(name));
}

int	is_builtin(t_tokens token_lst[0])
{
	auto char *builtins[] = {"exit", "cd", NULL};
	int	i;

	i = -1;
	while (builtins[++i])
		if (token_lst[0] && !ft_strcmp(builtins[i], token_lst[0]))
			return (1);
	return (0);
}

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
