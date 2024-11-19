/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:06:26 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/14 21:06:54 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"
#include <stdlib.h>

//TODO: handle -nnnnnnn?
//TODO: handle printf errors?

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int nflag;

	i = 1;
	nflag = 0;
	if ((cmd->opt[1]) && ft_strncmp(cmd->opt[1], "-n", 2))
	{
		nflag = 1;
		i++;
	}
	i--;
	while (cmd->opt[++i])
	{
		printf("%s", cmd->opt[i]);
		if (cmd->opt[i] && cmd->opt[i + 1])
			printf(" ");
	}
	if (!nflag)
		printf("\n");
	return (EXIT_SUCCESS);
}
