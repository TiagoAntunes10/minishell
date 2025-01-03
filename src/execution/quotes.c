/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:51 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/03 12:50:09 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	quotes_pairs(char *str, t_envp *envp, int is_bt)
{
	int	sin_quote;
	int	dou_quote;

	sin_quote = 0;
	dou_quote = 0;
	if (!str)
		return (-1);
	while (*str != 0)
	{
		if (*str == '"')
			dou_quote++;
		else if (*str == '\'')
			sin_quote++;
		str++;
	}
	if (dou_quote % 2 != 0 || sin_quote % 2 != 0)
	{
		stat_ret(RED QUOTE_ERR RST, 2);
		if (is_bt)
			return (-1);
		exit_failure(envp->root, NULL, envp);
	}
	return (0);
}

static unsigned int	quotes_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '"' && *str != '\'' && *(str++) != 0)
		len++;
	if (len == 0 && (*str == '"' || *str == '\''))
		len += check_quotes(&str, len) + 1;
	return (len);
}

static unsigned int	strs_in_arg(char *str)
{
	int	count;

	count = 0;
	while (*str != 0)
	{
		str += quotes_strlen(str);
		count++;
	}
	return (count);
}

static char	**split_arg(char *str, t_envp *envp)
{
	char			**arr;
	char			**arr_cpy;
	unsigned int	len;

	arr = (char **) safe_alloc(strs_in_arg(str) + 1, sizeof(char *),
			envp->root, envp);
	arr_cpy = arr;
	while (*str != 0)
	{
		len = quotes_strlen(str);
		*arr_cpy = malloc(len + 1);
		if (*arr_cpy == NULL)
		{
			clear_arr(arr);
			exit_failure(envp->root, NULL, envp);
		}
		ft_strlcpy(*arr_cpy, str, len + 1);
		arr_cpy++;
		str += len;
	}
	*arr_cpy = NULL;
	return (arr);
}

char	*clean_str(char *origin, t_envp *envp, int here_doc)
{
	char			**origin_split;
	char			**split_cpy;

	if (!origin)
		return (free(origin), NULL);
	origin_split = split_arg(origin, envp);
	split_cpy = origin_split;
	while (*split_cpy != NULL)
	{
		check_dolla(split_cpy, envp, here_doc);
		remove_quotes(split_cpy, here_doc);
		split_cpy++;
	}
	free(origin);
	origin = conc_str(origin_split, envp);
	clear_arr(origin_split);
	return (origin);
}
