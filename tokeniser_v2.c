/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/03 21:28:58 by tialbert         ###   ########.fr       */
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

// TODO: Handle parenthesis
int	count_opt(char **tokens)
{
	int		count;
	char	**token_cpy;

	count = 0;
	token_cpy = tokens;
	while (*token_cpy != NULL && **token_cpy != '>' && **token_cpy != ';' &&
			**token_cpy != '|' && **token_cpy != '<' &&
			ft_strncmp(*token_cpy, "<<", 2) != 0 &&
			ft_strncmp(*token_cpy, ">>", 2) != 0)
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


// TODO: How to handle ';' without parenthesis and a pipe - this might take a different function
// The current function works well with parenthesis
t_tree	*tokenisation(char *input)
{
	t_tree	*tree;
	char	**cmd_lst;
	char	**arr_cpy;

	cmd_lst = split_input(input);
	arr_cpy = cmd_lst;
	while (arr_cpy != NULL)
	{
		if (**arr_cpy == '<' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &(++arr_cpy), O_RDONLY);
		else if (ft_strncmp(*arr_cpy, "<<", 2) && ft_strlen(*arr_cpy) == 2)
			tree = delim_node(tree, &(++arr_cpy));
		else if (**arr_cpy == '>' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &(++arr_cpy), O_WRONLY | O_CREAT);
		else if (ft_strncmp(*arr_cpy, ">>", 2) && ft_strlen(*arr_cpy) == 2)
			tree = redir_node(tree, &(++arr_cpy), O_WRONLY | O_CREAT | O_APPEND);
		else if (**arr_cpy == '|' && ft_strlen(*arr_cpy) == 1)
			tree = pipe_node(tree);
		else if (**arr_cpy == ';' && ft_strlen(*arr_cpy) == 1)
			tree = lst_node(tree);
		else
			tree = cmd_node(tree, &arr_cpy);
	}
	clear_arr(cmd_lst);
}
