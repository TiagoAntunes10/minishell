/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/17 21:36:03 by tialbert         ###   ########.fr       */
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

t_tokens	*clear_lst(t_tokens *tokens)
{
	t_tokens	*cpy;

	while (tokens != NULL)
	{
		free(tokens->cmd);
		clear_arr(tokens->options);
		if (tokens->infile != NULL)
			free(tokens->infile);
		if (tokens->outfile != NULL)
			free(tokens->outfile);
		cpy = tokens->next;
		free(tokens);
		tokens = cpy;
	}
	return (NULL);
}

//TODO: Check if there are cases where more than one fd is open
//TODO: Maybe this function does not need to close fds
void	exit_success(t_tokens *tokens, int fd)
{
	while (tokens->prev != NULL)
		tokens = tokens->prev;
	clear_lst(tokens);
	if (fd != 0)
		close(fd);
	exit(EXIT_SUCCESS);
}

//TODO: Maybe this function should handle closing pipes
void	exit_failure(t_tokens *tokens, int fd)
{
	while (tokens->prev != NULL)
		tokens = tokens->prev;
	clear_lst(tokens);
	if (fd != 0)
		close(fd);
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
