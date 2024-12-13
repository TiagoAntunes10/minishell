/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:20:19 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/13 18:40:44 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static unsigned int	check_quotes(char **str, int len)
{
	int				quotes;

	quotes = 0;
	if (**str == '"')
		quotes = 1;
	else if (**str == '\'')
		quotes = 2;
	while (quotes > 0)
	{
		(*str)++;
		if (((**str == '"' && quotes == 1)
			|| (**str == '\'' && quotes == 2)) || **str == 0)
		{
			quotes = 0;
			break ;
		}
		len++;
	}
	return (len);
}

unsigned int	mod_strlen(char *str)
{
	unsigned int	len;

	len = 0;
	while (*str != ' ' && *str != 0)
	{
		len = check_quotes(&str, len);
		if (*str != '"' && *str != '\'' && *str != '(' && *str != ')')
			len++;
		str++;
	}
	return (len);
}

int	count_words(char *str)
{
	int		count;

	count = 0;
	while (*str != 0)
	{
		if (*str == '"' || *str == '\'')
		{
			str += mod_strlen(str);
			str += 2;
		}
		else
			str += mod_strlen(str);
		count++;
		while (*str == ' ' || *str == ')')
			str++;
	}
	return (count);
}

char	**split_input(char *str, t_envp *envp)
{
	char			**word_arr;
	char			**word_arr_cp;
	unsigned int	len;

	word_arr = (char **) safe_alloc(count_words(str) + 1, sizeof(char *),
								 NULL, envp);
	word_arr_cp = word_arr;
	while (*str != 0)
	{
		while (*str == ' ')
			str++;
		if (*str == 0)
			break ;
		len = mod_strlen(str);
		if (*str == '"' || *str == '\'' || *str == '(')
			str++;
		*word_arr_cp = (char *) split_alloc(len + 1, 1, word_arr, envp);
		ft_strlcpy(*word_arr_cp, str, len + 1);
		word_arr_cp++;
		str += len;
		if (*str == '"' || *str == '\'' || *str == ')')
			str++;
	}
	*word_arr_cp = NULL;
	return (word_arr);
}
