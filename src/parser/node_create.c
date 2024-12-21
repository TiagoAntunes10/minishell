/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:20:52 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/21 15:29:49 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static char	**get_opt(t_cmd *cmd, t_tree *tree, char **input, t_envp *envp)
{
	int		opt_num;
	int		i;

	opt_num = count_opt(input);
	cmd->opt = malloc((opt_num + 1) * sizeof(char *));
	if (cmd->opt == NULL)
	{
		clear_tree((t_tree *) cmd);
		exit_failure(tree, NULL, envp);
	}
	i = 0;
	while (i < opt_num)
	{
		cmd->opt[i] = malloc(ft_strlen(*input) + 1);
		if (cmd->opt == NULL)
		{
			clear_tree((t_tree *) cmd);
			exit_failure(tree, NULL, envp);
		}
		ft_strlcpy(cmd->opt[i++], *input, ft_strlen(*input) + 1);
		input++;
	}
	cmd->opt[i] = NULL;
	return (input);
}

t_tree	*cmd_node(t_tree *tree, char **input, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) safe_alloc(sizeof(*cmd), 1, tree, envp);
	cmd->type = CMD;
	cmd->cmd = (char *) safe_alloc(ft_strlen(*input) + 1, 1, tree, envp);
	ft_strlcpy(cmd->cmd, *input, ft_strlen(*input) + 1);
	input = get_opt(cmd, tree, input, envp);
	if (tree != NULL)
	{
		tree = org_tree(tree, (t_tree *) cmd);
		tree = token_dist(tree, envp, input);
		return (tree);
	}
	tree = token_dist((t_tree *) cmd, envp, input);
	return (tree);
}

t_tree	*delim_node(t_tree *tree, char **input, t_envp *envp)
{
	t_delim	*delim;

	input++;
	delim = (t_delim *) safe_alloc(sizeof(*delim), 1, tree, envp);
	delim->type = DELIM;
	delim->delim = malloc(ft_strlen(*input) + 1);
	bzero(delim->delim, ft_strlen(*input) + 1);
	if (delim->delim == NULL)
	{
		free(delim);
		exit_failure(tree, NULL, envp);
	}
	ft_strlcpy(delim->delim, *input, ft_strlen(*input) + 1);
	delim->right = tree;
	input++;
	tree = token_dist((t_tree *) delim, envp, input);
	return (tree);
}

t_tree	*pipe_node(t_tree *tree, char **input, t_envp *envp)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) safe_alloc(sizeof(*pipe), 1, tree, envp);
	pipe->type = PIPE;
	pipe->left = tree;
	pipe->right = NULL;
	input++;
	tree = token_dist((t_tree *) pipe, envp, input);
	return (tree);
}

t_tree	*redir_node(t_tree *tree, char **input, int mode, t_envp *envp)
{
	t_redir	*redir;

	input++;
	redir = (t_redir *) safe_alloc(sizeof(*redir), 1, tree, envp);
	redir->type = REDIR;
	redir->file = NULL;
	if (mode == (O_WRONLY | O_CREAT))
		check_outfile(*input, mode, tree, envp);
	if (*input != NULL)
	{
		redir->file = malloc(ft_strlen(*input) + 1);
		if (redir->file == NULL)
		{
			free(redir);
			exit_failure(tree, NULL, envp);
		}
		ft_strlcpy(redir->file, *input, ft_strlen(*input) + 1);
		input++;
	}
	redir->mode = mode;
	redir->right = tree;
	tree = token_dist((t_tree *) redir, envp, input);
	return (tree);
}
