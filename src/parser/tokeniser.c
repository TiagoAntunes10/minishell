/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/30 23:10:12 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	**ignore_redir(char ***input, char **input_cpy)
{
	if (input_cpy == NULL)
		input_cpy = *input;
	(*input)++;
	return (input_cpy);
}

char	**ignore_opt(char **input)
{
	while (*input != NULL && **input != '|'
		&& **input != '<' && **input != '>'
		&& ft_strncmp(*input, "<<", ft_strlen(*input)) != 0
		&& ft_strncmp(*input, ">>", ft_strlen(*input)) != 0)
		input++;
	return (input);
}

int	count_opt(char **tokens)
{
	int		count;
	char	**token_cpy;

	count = 0;
	token_cpy = tokens;
	while (*token_cpy != NULL && **token_cpy != '|')
	{
		if (redir_check(*token_cpy) == 0)
			count++;
		else
			token_cpy++;
		if (*token_cpy != NULL)
			token_cpy++;
	}
	return (count);
}

t_tree	*token_dist(t_tree *tree, t_envp *envp, char **input)
{
	if (*input == NULL)
		return (tree);
	if (**input == '<' && ft_strlen(*input) == 1)
		return (redir_node(tree, input, O_RDONLY, envp));
	else if (ft_strncmp(*input, "<<", ft_strlen(*input)) == 0)
		return (delim_node(tree, input, envp));
	else if (**input == '>' && ft_strlen(*input) == 1)
		return (redir_node(tree, input, O_WRONLY | O_CREAT, envp));
	else if (ft_strncmp(*input, ">>", ft_strlen(*input)) == 0)
		return (redir_node(tree, input,
				O_WRONLY | O_CREAT | O_APPEND, envp));
	else if (**input == '|' && ft_strlen(*input) == 1)
		return (pipe_node(tree, input, envp));
	else
		return (cmd_node(tree, input, envp));
}

t_tree	*tokenisation(char *input, t_envp *envp)
{
	t_tree	*tree;

	envp->input_arr = split_input(input, envp);
	tree = NULL;
	tree = token_dist(tree, envp, envp->input_arr);
	envp->input_arr = clear_arr(envp->input_arr);
	return (tree);
}
