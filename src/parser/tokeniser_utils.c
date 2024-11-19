/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:20:19 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/04 22:11:26 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	mod_strlen(char *str)
{
	unsigned int	len;
	int				quotes;
	char			*str_cpy;

	quotes = 0;
	len = 0;
	str_cpy = str;
	while (*str_cpy != ' ' && *str_cpy != 0)
	{
		if (*str_cpy == '"')
			quotes = 1;
		else if (*str_cpy == '\'')
			quotes = 2;
		while (quotes > 0)
		{
			str_cpy++;
			if (((*str_cpy == '"' && quotes == 1) || (*str_cpy == '\'' && quotes == 2)) || *str_cpy == 0)
				quotes = 0;
			len++;
		}
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
		str += mod_strlen(str);
		if (*str == '"' || *str == '\'')
			str++;
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