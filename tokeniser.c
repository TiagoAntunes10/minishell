/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/09/22 18:14:21 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

static void	infile_record(t_tokens **token_lst, char ***tokens)
{
	free(**tokens);
	(*tokens)++;
	if (**tokens == NULL)
	{
		(*token_lst)->infile = NULL;
		return ;
	}
	else
	{
		(*token_lst)->infile = malloc(sizeof(*tokens));
		if ((*token_lst)->infile == NULL)
			return ;
		ft_strlcpy((*token_lst)->infile, **tokens, ft_strlen(**tokens) + 1);
	}
	free(**tokens);
	(*tokens)++;
}

static void	outfile_record(t_tokens **token_lst, char ***tokens)
{
	free(**tokens);
	(*tokens)++;
	if (**tokens == NULL)
	{
		(*token_lst)->outfile = NULL;
		return ;
	}
	else
	{
		(*token_lst)->outfile = malloc(sizeof(*tokens));
		if ((*token_lst)->outfile == NULL)
			return ;
		ft_strlcpy((*token_lst)->outfile, **tokens, ft_strlen(**tokens) + 1);
	}
	free(**tokens);
	(*tokens)++;
}

static int	count_opt(char **tokens)
{
	int		count;
	char	**token_cpy;

	count = 0;
	token_cpy = tokens;
	while (*token_cpy != NULL && ft_strncmp(*token_cpy, ">", 1) != 0 &&
			ft_strncmp(*token_cpy, "|", 1) != 0 &&
			ft_strncmp(*(token_cpy++), "<", 1) != 0)
		count++;
	return (count);
}

static void	cmd_record(t_tokens **token_lst, char ***tokens)
{
	int	i;
	int	option_num;

	option_num = count_opt(*tokens);
	(*token_lst)->cmd = malloc(ft_strlen(**tokens) + 1);
	if ((*token_lst)->cmd == NULL)
		return ;
	ft_strlcpy((*token_lst)->cmd, **tokens, ft_strlen(**tokens) + 1);
	(*token_lst)->options = malloc((option_num + 1) * sizeof(char *));
	//TODO: Maybe create an error handling function that terminates the program
	if ((*token_lst)->options == NULL)
		return ;
	i = 0;
	while (i < option_num)
	{
		(*token_lst)->options[i] = malloc(ft_strlen(**tokens) + 1);
		if ((*token_lst)->options[i] == NULL)
			return ;
		ft_strlcpy((*token_lst)->options[i++], **tokens, ft_strlen(**tokens) + 1);
		free(**tokens);
		(*tokens)++;
	}
	(*token_lst)->options[i] = NULL;
}


t_tokens	*tokenisation(char *input)
{
	char		**tokens;
	char		**arr_cpy;
	t_tokens	*token_lst;
	t_tokens	*token_cpy;

	tokens = split_input(input);
	arr_cpy = tokens;
	token_lst = create_lst(tokens);
	token_cpy = token_lst;
	while (*tokens != NULL)
	{
		if (ft_strncmp(*tokens, "<", 1) == 0 && ft_strlen(*tokens) == 1)
			infile_record(&token_cpy, &tokens);
		else if (ft_strncmp(*tokens, ">", 1) == 0 && ft_strlen(*tokens) == 1)
			outfile_record(&token_cpy, &tokens);
		else
			cmd_record(&token_cpy, &tokens);
		if (*tokens != NULL && ft_strncmp(*tokens, "|", 1) == 0 && ft_strlen(*tokens) == 1)
		{
			token_cpy = token_cpy->next;
			free(*(tokens++));
		}
	}
	free(arr_cpy);
	return (token_lst);
}
