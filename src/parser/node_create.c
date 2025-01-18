/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:20:52 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 21:53:11 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	**get_opt(t_cmd *cmd, t_tree *tree, char **input, t_envp *envp)
{
	int		i;
	char	**input_cpy;

	input_cpy = NULL;
	i = 0;
	while (i < cmd->num_opt)
	{
		if (redir_check(*input) == 0)
		{
			cmd->opt[i] = malloc(ft_strlen(*input) + 1);
			if (cmd->opt[i] == NULL)
				clean_cmd((t_tree *) cmd, tree, envp);
			ft_strlcpy(cmd->opt[i++], *input, ft_strlen(*input) + 1);
		}
		else
			input_cpy = ignore_redir(&input, input_cpy);
		if (*input != NULL)
			input++;
	}
	cmd->opt[i] = NULL;
	if (input_cpy != NULL)
		return (input_cpy);
	return (input);
}

t_tree	*cmd_node(t_tree *tree, char **input, t_envp *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) safe_alloc(sizeof(*cmd), 1, tree, envp);
	cmd->type = CMD;
	cmd->cmd = (char *) safe_alloc(ft_strlen(*input) + 1, 1, tree, envp);
	ft_strlcpy(cmd->cmd, *input, ft_strlen(*input) + 1);
	cmd->num_opt = count_opt(input);
	cmd->opt = malloc((cmd->num_opt + 1) * sizeof(char *));
	if (cmd->opt == NULL)
		clean_cmd((t_tree *) cmd, tree, envp);
	input = get_opt(cmd, tree, input, envp);
	if (*input != NULL && ft_strncmp(*input, "||", lencmp(*input, "||")) == 0)
		input++;
	if (tree != NULL)
	{
		org_tree(tree, (t_tree *) cmd);
		tree = token_dist(tree, envp, input);
		return (tree);
	}
	tree = token_dist((t_tree *) cmd, envp, input);
	return (tree);
}

static int	read_here_doc(char *delim, int *inp_pipe, t_envp *envp)
{
	char	*line;

	if (!is_redir_valid(delim))
		return (-1);
	// end_heredoc(envp, inp_pipe, 0);
	// if (dup2(envp->fd_in, 0) == -1 || dup2(envp->fd_out, 1) == -1)
	// 	exit_failure(envp->root, inp_pipe, envp);
	line = readline(">");
	line = clean_str(line, envp, 1);
	while (1)
	{
		if (!line)
			break ;
		if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
			return (free(line), 0);
		if (write(inp_pipe[1], line, ft_strlen(line)) == -1
			|| write(inp_pipe[1], "\n", 1) == -1)
			exit_failure(envp->root, inp_pipe, envp);
		free(line);
		line = readline(">");
		line = clean_str(line, envp, 1);
	}
	free(line);
	printf(HEREDOC_EOF" (wanted '%s')\n", delim);
	return (-1);
}

t_tree	*delim_node(t_tree *tree, char **input, t_envp *envp)
{
	t_delim	*delim;
	int		inp_pipe[2];

	input++;
	delim = (t_delim *) safe_alloc(sizeof(*delim), 1, tree, envp);
	delim->type = DELIM;
	delim->fd = -1;
	delim->delim = malloc(ft_strlen(*input) + 1);
	if (delim->delim == NULL)
	{
		free(delim);
		exit_failure(tree, NULL, envp);
	}
	bzero(delim->delim, ft_strlen(*input) + 1);
	ft_strlcpy(delim->delim, *input, ft_strlen(*input) + 1);
	if (delim->delim[0] != 0)
	{
		quotes_pairs(delim->delim, envp, 0);
		remove_quotes(&(delim->delim), 0, envp);
		if (pipe(inp_pipe) == -1)
			exit_failure(envp->root, NULL, envp);
		delim->fd = inp_pipe[0];
		if (read_here_doc(delim->delim, inp_pipe, envp) == -1)
		{
			close(delim->fd);
			free(delim->delim);
			free(delim);
			close(inp_pipe[1]);
			clear_tree(tree);
			return (NULL);
		}
		close(inp_pipe[1]);
	}
	if (*input != NULL)
		input++;
	if (check_cmd(tree) == 1)
		input = ignore_opt(input);
	tree = org_delim(delim, tree);
	tree = token_dist(tree, envp, input);
	return (tree);
}

t_tree	*pipe_node(t_tree *tree, char **input, t_envp *envp)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) safe_alloc(sizeof(*pipe), 1, tree, envp);
	pipe->type = PIPE;
	if (tree != NULL && tree->type == PIPE)
		tree_leafs_pipe(tree, pipe);
	else
		pipe->left = tree;
	pipe->right = NULL;
	input++;
	if (*input == NULL || **input == '|')
	{
		if (tree != NULL && tree->type != PIPE)
			clear_tree(tree);
		free(pipe);
		stat_ret(RED PIPE_ERR RST, 2);
		return (NULL);
	}
	if (tree != NULL && tree->type == PIPE)
		tree = token_dist(tree, envp, input);
	else
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
	if (*input != NULL)
	{
		redir->file = malloc(ft_strlen(*input) + 1);
		if (redir->file == NULL)
		{
			free(redir);
			exit_failure(tree, NULL, envp);
		}
		ft_strlcpy(redir->file, *input, ft_strlen(*input) + 1);
		if (mode == (O_WRONLY | O_CREAT))
			check_outfile(redir, mode, envp, tree);
		input++;
	}
	if (check_cmd(tree) == 1)
		input = ignore_opt(input);
	redir->mode = mode;
	tree = org_redir_read(redir, tree);
	tree = token_dist(tree, envp, input);
	return (tree);
}
