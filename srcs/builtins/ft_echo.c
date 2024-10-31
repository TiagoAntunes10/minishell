/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:56:19 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/20 18:01:18 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_echo(t_tokens *token_lst, int start)
{
	while (token_lst->options[start + 1] != NULL)
	{
		if (*token_lst->options[1] == '$' && ft_strlen(token_lst->options[start]) > 1)
			dollar_sub(token_lst, start);
		//if (printf("%s ", token_lst->options[start++]) == -1)
			//TODO: Write error handling function with errno
	}
	if (*token_lst->options[1] == '$' && ft_strlen(token_lst->options[start]) > 1)
		dollar_sub(token_lst, start);
	//if (printf("%s", token_lst->options[start++]) == -1)
		//TODO: Write error handling function with errno
}

//TODO: Make ft_echo tests
void	ft_echo(t_tokens *token_lst, int *pipe)
{
/*	if (pipe != NULL)
	{
		if (dup2(1, pipe[1]) == -1)
			//TODO: Write error handling function with errno
	}*/
	if (ft_strncmp(token_lst->options[1], "-n", 2) == 0 && ft_strlen(token_lst->options[1]) == 2)
		write_echo(token_lst, 2);
	else
	{
		write_echo(token_lst, 1);
	//	if (printf("\n") == -1)
			//TODO: Write error handling function with errno
	}
	close(pipe[1]);
}
