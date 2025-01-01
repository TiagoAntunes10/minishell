/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:54:09 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/01 16:56:59 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	remove_quotes(char **arr, int here_doc)
{
	char	*str;

	if ((**arr == '\'' || **arr == '"') && here_doc == 0)
	{
		str = ft_substr(*arr, 1, ft_strlen(*arr) - 2);
		free(*arr);
		*arr = ft_substr(str, 0, ft_strlen(str));
		free(str);
	}
}
