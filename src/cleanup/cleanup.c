/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/26 21:11:27 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	clear_envp(t_envp *envp)
{
	t_envp	*envp_cpy;

	envp_cpy = envp->next;
	while (envp != NULL)
	{
		free(envp->key);
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
void	exit_success(t_tree *tree, int fd)
{
	if (tree != NULL)
		clear_tree(tree);
	if (fd != -1)
		close(fd);
	exit(EXIT_SUCCESS);
}

//TODO: Maybe this function should handle closing pipes
void	exit_failure(t_tree *tree, int fd)
{
	if (tree != NULL)
		clear_tree(tree);
	if (fd != -1)
		close(fd);
	perror(strerror(errno));
	exit(errno);
}
