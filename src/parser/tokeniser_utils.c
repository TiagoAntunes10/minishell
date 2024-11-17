/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:20:19 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/17 18:07:18 by tialbert         ###   ########.fr       */
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
	else if (**str == '(' || **str == ')')
		(*str)++;
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
	char			*str_cpy;

	len = 0;
	str_cpy = str;
	while (*str_cpy != ' ' && *str_cpy != 0)
	{
		len = check_quotes(&str_cpy, len);
		if (*str_cpy != '"' && *str_cpy != '\'')
			len++;
		str_cpy++;
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
		while (*str == ' ')
			str++;
	}
	return (count);
}

// TODO: Reduce lines
// TODO: Refactor to handle () and ';' - these chars will not be separated by a space
// TODO: I want to keep the () and ';' in the array of strings
char	**split_input(char *str)
{
	char			**word_arr;
	char			**word_arr_cp;
	unsigned int	len;

	word_arr = malloc((count_words(str) + 1) * sizeof(char *));
	//TODO: Maybe create an error handling function that terminates the program
	if (word_arr == NULL)
		return (NULL);
	word_arr_cp = word_arr;
	while (*str != 0)
	{
		while (*str == ' ')
			str++;
		if (*str == 0)
			break ;
		len = mod_strlen(str);
		if (*str == '"' || *str == '\'')
			str++;
		*word_arr_cp = malloc(len + 1);
		//TODO: Maybe create an error handling function that terminates the program
		if (*word_arr_cp == NULL)
			return (clear_arr(word_arr));
		ft_strlcpy(*word_arr_cp, str, len + 1);
		word_arr_cp++;
		str += len;
		if (*str == '"' || *str == '\'')
			str++;
	}
	*word_arr_cp = NULL;
	return (word_arr);
}
