/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/14 21:54:29 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "minishell.h"
=======
#include "../../Include/minishell.h"
>>>>>>> 91d655cd368eec5976dfca42dd733e0176863e75

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
