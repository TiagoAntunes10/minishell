/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:04 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/20 21:33:12 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	count_opt(char **tokens)
{
	int		count;
	char	**token_cpy;

	count = 0;
	token_cpy = tokens;
	while (*token_cpy != NULL && **token_cpy != '>' &&
			**token_cpy != '|' && **token_cpy != '<' &&
			ft_strncmp(*token_cpy, "<<", ft_strlen(*token_cpy)) != 0 &&
			ft_strncmp(*token_cpy, ">>", ft_strlen(*token_cpy)) != 0)
	{
		count++;
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
