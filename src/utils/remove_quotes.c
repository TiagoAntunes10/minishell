/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:54:09 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 17:00:55 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	str_cleaner(char **arr, int quotes, t_envp *envp)
{
	char	*str_arr[3];
	char	*arr_cpy;

	arr_cpy = *arr;
	str_arr[2] = NULL;
	while (*arr_cpy != 0)
	{
		if ((*arr_cpy == '"' && quotes == 2)
			|| (*arr_cpy == '\'' && quotes == 1))
		{
			str_arr[0] = ft_substr(*arr, 0, arr_cpy - (*arr));
			str_arr[1] = ft_substr(arr_cpy, 1, ft_strlen(arr_cpy + 1));
			free(*arr);
			*arr = conc_str(str_arr, envp);
			free(str_arr[0]);
			free(str_arr[1]);
			arr_cpy = *arr;
		}
		arr_cpy++;
	}
}

void	remove_quotes(char **arr, int here_doc, t_envp *envp)
{
	char	*str;
	int		quotes;

	quotes = 0;
	if (here_doc == 0)
	{
		if (**arr == '\'')
			quotes = 1;
		else if (**arr == '"')
			quotes = 2;
		if (quotes > 0)
		{
			str = ft_substr(*arr, 1, ft_strlen(*arr) - 2);
			free(*arr);
			*arr = ft_substr(str, 0, ft_strlen(str));
			free(str);
		}
		if (*arr != NULL)
			str_cleaner(arr, quotes, envp);
	}
}
