/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/24 18:01:39 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"


static char	*conc_path(char *cmd, char *path)
{
	char	*cmd_path;
	int		size;

	size = ft_strlen(cmd) + ft_strlen(path) + 2;
	cmd_path = malloc(size);
	if (cmd_path == NULL)
		// TODO:Clear path and exit the program
	ft_strlcat(cmd_path, path, ft_strlen(path) + 1);
	ft_strlcat(cmd_path, "/", ft_strlen(path) + 2);
	ft_strlcat(cmd_path, cmd, size + 1);
	return (cmd_path);
}

static char	*find_path(char *cmd, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_path;
	int		size;

	envp_path = ft_split(search_envp(envp, "PATH")->value, ':');
	if (access(cmd, F_OK) == -1)
	{
		while (*envp_path != NULL)
		{
			cmd_path = conc_path(cmd, *envp_path);
			if (access(cmd_path, F_OK | X_OK) == 1)
				return (cmd_path);
			free(cmd_path);
			envp_path++;
		}
	}
	else
	{
		if (access(cmd, X_OK) == -1)
			// TODO: Handle error "the file is not executable" and clear envp_path
	}
	cmd_path = ft_substr(cmd, 0, ft_strlen(cmd));
	return (cmd_path);
}

void	std_cmd(t_cmd *cmd, t_envp *envp)
{
	char	**envp_arr;
	char	*cmd_path;

	envp_arr = lst_to_arr(envp);
	cmd_path = find_path(cmd->cmd, envp);
	if (execve(cmd_path, cmd->opt, envp_arr) == -1)
		// TODO: Exit error function
	// TODO: Not sure if this is necessary
	// clear_arr(envp_arr);
	// free(cmd_path);
}
