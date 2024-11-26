/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/26 20:56:59 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Handle parenthesis
int	count_opt(char **tokens)
{
	int		count;
	char	**token_cpy;

	count = 0;
	token_cpy = tokens;
	while (*token_cpy != NULL && **token_cpy != '>' && **token_cpy != ';' &&
			**token_cpy != '|' && **token_cpy != '<' &&
			ft_strncmp(*token_cpy, "<<", ft_strlen(*token_cpy)) != 0 &&
			ft_strncmp(*token_cpy, ">>", ft_strlen(*token_cpy)) != 0)
	{
		count++;
		token_cpy++;
	}
	return (count);
}

// TODO: Reduce number of lines
// TODO: Check if the flags for the open fuction are passed correctly (var type problem???)
t_tree	*tokenisation(char *input)
{
	t_tree	*tree;
	char	**cmd_lst;
	char	**arr_cpy;

	cmd_lst = split_input(input);
	arr_cpy = cmd_lst;
	tree = NULL;
	while (*arr_cpy != NULL)
	{
		if (**arr_cpy == '<' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &arr_cpy, O_RDONLY);
		else if (ft_strncmp(*arr_cpy, "<<", ft_strlen(*arr_cpy)) == 0)
			tree = delim_node(tree, &arr_cpy);
		else if (**arr_cpy == '>' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &arr_cpy, O_WRONLY | O_CREAT);
		else if (ft_strncmp(*arr_cpy, ">>", ft_strlen(*arr_cpy)) == 0)
			tree = redir_node(tree, &arr_cpy, O_WRONLY | O_CREAT | O_APPEND);
		else if (**arr_cpy == '|' && ft_strlen(*(arr_cpy++)) == 1)
			tree = pipe_node(tree);
		else
			tree = cmd_node(tree, &arr_cpy);
	}
	clear_arr(cmd_lst);
	return (tree);
}
