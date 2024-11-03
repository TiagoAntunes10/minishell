/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:20:52 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/03 17:45:43 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

// TODO: Maybe create a function that safely alloc memory
t_tree	*cmd_node(t_tree *tree, char ***input)
{
	t_cmd	*cmd;
	int		opt_num;
	int		i;

	cmd->type = CMD;
	opt_num = count_opt(*input);
	cmd = malloc(sizeof(*cmd));
	cmd->cmd = malloc(ft_strlen(**input) + 1);
	//TODO: Maybe create an error handling function that terminates the program
	ft_strlcpy(cmd->cmd, **input, ft_strlen(**input) + 1);
	cmd->opt = malloc((opt_num + 1) * sizeof(char *));
	//TODO: Maybe create an error handling function that terminates the program
	i = 0;
	while (i < opt_num)
	{
		cmd->opt[i] = malloc(ft_strlen(**input) + 1);
		//TODO: Maybe create an error handling function that terminates the program
		ft_strlcpy(cmd->opt[i++], **input, ft_strlen(**input) + 1);
		(*input)++;
	}
	cmd->opt[i] = NULL;
	if (tree != NULL)
		tree = org_tree(tree, (t_tree *) cmd);
	return ((t_tree *) tree);
}

t_tree	*delim_node(t_tree *tree, char ***input)
{
	t_delim	*delim;

	delim->type = DELIM;
	delim->delim = malloc(ft_strlen(**input) + 1);
	ft_strlcpy(delim->delim, **input, ft_strlen(**input) + 1);
	delim->right = tree;
	return ((t_tree *) delim);
}
