/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:29:07 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/17 21:56:45 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	ft_export(t_tokens *token_lst, int *pipe)
{
	if (pipe != NULL)
	{
		if (dup2(1, pipe[1]) == -1)
			//TODO: Write error handling function with errno
	}

	close(pipe[1]);
}
