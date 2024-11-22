/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/20 21:56:38 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	**lst_to_arr(t_envp *envp)
{
	char	**arr;
	int		size;
	int		i;

	arr = malloc((lst_len(envp) + 1) * sizeof(char *));
	if (arr == NULL)
		// TODO: Exit program
	i = 0;
	while (envp != NULL)
	{
		size = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
		arr[i] = malloc(size);
		if (arr[i] == NULL)
			// TODO: Clear array and exit program
		ft_strlcat(arr[i], envp->key, ft_strlen(envp->key) + 1);
		ft_strlcat(arr[i], ":", ft_strlen(envp->key) + 2);
		ft_strlcat(arr[i++], envp->value, size);
	}
	return (arr);
}

static char	*conc_path(char *cmd, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_path;
	int		size;

	envp_path = get_path(envp);
	while (*envp_path != NULL)
	{
		size = ft_strlen(cmd) + ft_strlen(*envp_path) + 2;
		cmd_path = malloc(size);
		if (cmd_path == NULL)
			// TODO:Clear envp_path and exit the program
		ft_strlcat(cmd_path, *envp_path, ft_strlen(*envp_path) + 1);
		ft_strlcat(cmd_path, "/", ft_strlen(*envp_path) + 2);
		ft_strlcat(cmd_path, cmd, size + 1);
		if (access(cmd_path, F_OK | X_OK) == 1)
			return (cmd_path);
		free(cmd_path);
		envp_path++;
	}
	return (NULL);
}

void	std_cmd(t_cmd *cmd, t_envp *envp)
{
	char	**envp_arr;
	char	*cmd_path;

	envp_arr = lst_to_arr(envp);
	cmd_path = conc_path(cmd->cmd, envp);
	if (execve(cmd_path, cmd->opt, envp_arr) == -1)
		// TODO: Exit error function
	clear_arr(envp_arr);
	free(cmd_path);
}
