/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:20:52 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/05 22:28:44 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

// TODO: Maybe create a function that safely alloc memory
// TODO: Clean input variable
t_tree	*cmd_node(t_tree *tree, char ***input)
{
	t_cmd	*cmd;
	int		opt_num;
	int		i;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		exit_failure(tree, -1);
	cmd->type = CMD;
	opt_num = count_opt(*input);
	cmd->cmd = malloc(ft_strlen(**input) + 1);
	if (cmd->cmd == NULL)
		exit_failure(tree, -1);
	ft_strlcpy(cmd->cmd, **input, ft_strlen(**input) + 1);
	cmd->opt = malloc((opt_num + 1) * sizeof(char *));
	if (cmd->opt == NULL)
	{
		free(cmd->cmd);
		exit_failure(tree, -1);
	}
	i = 0;
	while (i < opt_num)
	{
		cmd->opt[i] = malloc(ft_strlen(**input) + 1);
		if (cmd->opt == NULL)
		{
			free(cmd->cmd);
			clear_arr(cmd->opt);
			exit_failure(tree, -1);
		}
		ft_strlcpy(cmd->opt[i++], **input, ft_strlen(**input) + 1);
		(*input)++;
	}
	cmd->opt[i] = NULL;
	if (tree != NULL)
		tree = org_tree(tree, (t_tree *) cmd);
	return (tree);
}

t_tree	*delim_node(t_tree *tree, char ***input)
{
	t_delim	*delim;

	delim = malloc(sizeof(*delim));
	//TODO: Maybe create an error handling function that terminates the program
	delim->type = DELIM;
	delim->delim = malloc(ft_strlen(**input) + 1);
	//TODO: Maybe create an error handling function that terminates the program
	ft_strlcpy(delim->delim, **input, ft_strlen(**input) + 1);
	delim->right = tree;
	return ((t_tree *) delim);
}

t_tree	*pipe_node(t_tree *tree)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(*pipe));
	//TODO: Maybe create an error handling function that terminates the program
	pipe->type = PIPE;
	pipe->left = tree;
	pipe->right = NULL;
	return ((t_tree *) pipe);
}

t_tree	*lst_node(t_tree *tree)
{
	t_lst	*lst;

	lst = malloc(sizeof(*lst));
	//TODO: Maybe create an error handling function that terminates the program
	lst->type = LIST;
	lst->left = tree;
	lst->right = NULL;
	return ((t_tree *) lst);
}

t_tree	*redir_node(t_tree *tree, char ***input, int mode)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	redir->file = malloc(ft_strlen(**input) + 1);
	//TODO: Maybe create an error handling function that terminates the program
	ft_strlcpy(redir->file, **input, ft_strlen(**input) + 1);
	(*input)++;
	redir->mode = mode;
	redir->right = tree;
	return ((t_tree *) redir);
}
