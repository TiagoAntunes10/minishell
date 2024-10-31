/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:56:45 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/31 17:31:57 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Write testing funcions for ft_pwd
void	ft_pwd(int *pipe)
{
	char	*cwd;

	/*if (pipe != NULL)
	{
		if (dup2(1, pipe[1]) == -1)
			//TODO: Write error handling function with errno
	}*/
	cwd = getcwd(NULL, 0);
	if (printf("%s\n", cwd) == -1)
		//TODO: Write error handling function
	free(cwd);
}
