/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/10 15:33:55 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exec_pipe(t_tree *tree, int fd, t_envp *envp)
{
	int		inp_pipe[2];
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *) tree;
	if (pipe_node->left == NULL || pipe_node->right == NULL)
	{
		ft_putstr_fd(RED PIPE_ERR RST, 2);
		g_exit_code = 2;
		exit_failure(envp->root, NULL, envp);
	}
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	signal_child();
	envp->id = fork();
	if (envp->id == -1)
		exit_failure(envp->root, inp_pipe, envp);
	else if (envp->id == 0)
	{
		pipe_in_pipe(inp_pipe, fd, envp);
		execution(pipe_node->right, 0, envp);
	}
	child_pipe(pipe_node, envp, inp_pipe);
}

static void	read_here_doc(char *delim, int *inp_pipe, t_envp *envp)
{
	char	*line;

	if (!is_redir_valid(delim))
		exit_failure(envp->root, inp_pipe, envp);
	end_heredoc(envp, inp_pipe, 0);
	if (dup2(envp->fd_in, 0) == -1 || dup2(envp->fd_out, 1) == -1)
		exit_failure(envp->root, inp_pipe, envp);
	line = readline(">");
	line = clean_str(line, envp, 1);
	while (1)
	{
		if (!line)
			break ;
		if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
			return (free(line));
		if (write(inp_pipe[1], line, ft_strlen(line)) == -1
			|| write(inp_pipe[1], "\n", 1) == -1)
			exit_failure(envp->root, inp_pipe, envp);
		free(line);
		line = readline(">");
		line = clean_str(line, envp, 1);
	}
	free(line);
	printf(HEREDOC_EOF" (wanted '%s')\n", delim);
}

void	exec_delim(t_tree *tree, t_envp *envp)
{
	t_delim	*delim;
	int		inp_pipe[2];

	delim = (t_delim *) tree;
	quotes_pairs(delim->delim, envp, 0);
	remove_quotes(&(delim->delim), 0, envp);
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	signal_heredoc();
	read_here_doc(delim->delim, inp_pipe, envp);
	if (dup2(inp_pipe[0], 0) == -1)
		exit_failure(envp->root, inp_pipe, envp);
	close(inp_pipe[1]);
	close(inp_pipe[0]);
	execution(delim->right, 0, envp);
	close(0);
}

//> = 65 | >> = 1089 | < = 0
void	exec_redir(t_tree *tree, t_envp *envp)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	if (is_redir_valid(redir->file) == 0)
		exit_failure(envp->root, NULL, envp);
	quotes_pairs(redir->file, envp, 0);
	remove_quotes(&(redir->file), 0, envp);
	if (redir->mode == O_RDONLY)
		redir_read(redir, envp);
	else
		redir_write(redir, envp);
}
