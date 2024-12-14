/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/13 18:40:26 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

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

t_tree	*tokenisation(char *input, t_envp *envp)
{
	t_tree	*tree;
	char	**cmd_lst;
	char	**arr_cpy;

	cmd_lst = split_input(input, envp);
	arr_cpy = cmd_lst;
	tree = NULL;
	while (*arr_cpy != NULL)
	{
		if (**arr_cpy == '<' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &arr_cpy, O_RDONLY, envp);
		else if (ft_strncmp(*arr_cpy, "<<", ft_strlen(*arr_cpy)) == 0)
			tree = delim_node(tree, &arr_cpy, envp);
		else if (**arr_cpy == '>' && ft_strlen(*arr_cpy) == 1)
			tree = redir_node(tree, &arr_cpy, O_WRONLY | O_CREAT, envp);
		else if (ft_strncmp(*arr_cpy, ">>", ft_strlen(*arr_cpy)) == 0)
			tree = redir_node(tree, &arr_cpy,
								O_WRONLY | O_CREAT | O_APPEND, envp);
		else if (**arr_cpy == '|' && ft_strlen(*(arr_cpy++)) == 1)
			tree = pipe_node(tree, envp);
		else
			tree = cmd_node(tree, &arr_cpy, envp);
	}
	clear_arr(cmd_lst);
	return (tree);
}
