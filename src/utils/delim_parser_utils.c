/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:58:10 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 23:46:53 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	read_here_doc(char *delim, int *inp_pipe, t_envp *envp)
{
	char	*line;

	if (!is_redir_valid(delim))
		return (-1);
	end_heredoc(envp, inp_pipe, 0);
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

int	receive_here_doc(t_delim *delim, t_tree *tree, t_envp *envp)
{
	int	inp_pipe[2];

	signal_heredoc();
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
			return (-1);
		}
		close(inp_pipe[1]);
	}
	return (0);
}

static void	tree_leafs_delim(t_tree *tree, t_delim *delim)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	while (pipe->right != NULL && pipe->right->type == PIPE)
		pipe = (t_pipe *) pipe->right;
	if (pipe->right != NULL && pipe->right->type == REDIR)
		org_delim(delim, pipe->right);
	else if (pipe->right != NULL && pipe->right->type == DELIM)
		org_delim(delim, pipe->right);
	else
	{
		delim->right = pipe->right;
		pipe->right = (t_tree *) delim;
	}
}

static void	order_delim(t_tree *tree, t_delim *delim)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	while (redir->right != NULL && redir->right->type == REDIR)
		redir = (t_redir *) redir->right;
	if (delim->right != NULL && delim->right->type == DELIM)
		org_delim(delim, delim->right);
	else
	{
		delim->right = redir->right;
		redir->right = (t_tree *) delim;
	}
}

t_tree	*org_delim(t_delim *delim, t_tree *tree)
{
	t_delim	*tree_delim;

	if (tree == NULL)
		return ((t_tree *) delim);
	else if (tree->type == REDIR)
		order_delim(tree, delim);
	else if (tree->type == PIPE)
		tree_leafs_delim(tree, delim);
	else if (tree->type == DELIM)
	{
		tree_delim = (t_delim *) tree;
		delim->right = tree_delim->right;
		tree_delim->right = (t_tree *) delim;
	}
	else
	{
		delim->right = tree;
		tree = (t_tree *) delim;
	}
	return (tree);
}
