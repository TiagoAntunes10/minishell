/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/11 22:05:29 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	clear_envp(t_envp *envp)
{
	t_envp	*envp_cpy;

	envp_cpy = envp->next;
	while (envp != NULL)
	{
		if (envp->key != NULL)
			free(envp->key);
		if (envp->value != NULL)
			free(envp->value);
		envp_cpy = envp->next;
		free(envp);
		envp = envp_cpy;
	}
}

char	**clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

//TODO: Check if there are cases where more than one fd is open
//TODO: Maybe this function does not need to close fds
void	exit_success(t_tree *tree, int fd, t_envp *envp)
{
	if (tree != NULL)
		clear_tree(tree);
	if (envp != NULL)
		clear_envp(envp);
	if (fd != -1)
		close(fd);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_tree *tree, int *fd, t_envp *envp)
{
	int	i;

	if (tree != NULL)
		clear_tree(tree);
	if (envp != NULL)
		clear_envp(envp);
	if (fd != NULL)
	{
		i = 0;
		while (i < 2)
			close(fd[i]);
	}
	perror(strerror(errno));
	exit(errno);
}
