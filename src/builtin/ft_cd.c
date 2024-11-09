/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:07:28 by tialbert          #+#    #+#             */
/*   Updated: 2024/09/29 16:04:09 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

//TODO: Make ft_cd tests
void	ft_cd(t_tokens *token_lst)
{
	char	*abs_path;
	char	*cwd;

	if(chdir(token_lst->options[1]) == -1)
	{
		if (errno == ENOENT)
		{
			cwd = getcwd(NULL, 0);
			abs_path = malloc(ft_strlen(token_lst->options[1]) + ft_strlen(cwd) + 1);
			if (abs_path == NULL)
			{
				free(cwd);
				//TODO: Error handling function
			}
			ft_strlcpy(abs_path, cwd, ft_strlen(cwd) + 1);
			free(cwd);
			ft_strlcat(abs_path, token_lst->options[1], ft_strlen(token_lst->options[1]) + ft_strlen(abs_path) + 1);
			if(chdir(abs_path) == -1)
				perror(strerror(errno));
			free(abs_path);
		}
		else
			perror(strerror(errno));
	}
}
