/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/05 22:23:24 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

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
	clear_tree(tree);
	if (fd != -1)
		close(fd);
	exit(EXIT_SUCCESS);
}

//TODO: Maybe this function should handle closing pipes
void	exit_failure(t_tree *tree, int fd)
{
	clear_tree(tree);
	if (fd != -1)
		close(fd);
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
