/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/11 22:33:42 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exec_pipe(t_tree *tree, int fd, t_envp *envp)
{
	int		inp_pipe[2];
	int		id;
	t_pipe	*pipe_node;
	int		status;

	pipe_node = (t_pipe *) tree;
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	id = fork();
	if (id == -1)
		exit_failure(envp->root, inp_pipe, envp);
	else if (id == 0)
		child_pipe(pipe_node, envp, inp_pipe);
	waitpid(-1, &status, WNOHANG);
	if (fd == 1 || fd == -1)
		pipe_in_pipe(inp_pipe, fd, envp);
	execution(pipe_node->right, 0, envp);
	exit_success(envp->root, 0, envp);
}

static void	read_here_doc(char *delim, int *inp_pipe, t_envp *envp)
{
	char	*line;
	
	line = get_next_line(0);
	while (ft_strncmp(delim, line, ft_strlen(line) - 1) != 0)
	{
		if (write(inp_pipe[1], line, ft_strlen(line)) == -1)
			exit_failure(envp->root, inp_pipe, envp);
		free(line);
		line = get_next_line(0);
	}
	free(line);
}

void	exec_delim(t_tree *tree, t_envp *envp)
{
	t_delim	*delim;
	int		inp_pipe[2];

	delim = (t_delim *) tree;
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	read_here_doc(delim->delim, inp_pipe, envp);
	if (dup2(inp_pipe[0], 0) == -1)
		exit_failure(envp->root, inp_pipe, envp);
	close(inp_pipe[1]);
	close(inp_pipe[0]);
	execution(delim->right, 0, envp);
	close(0);
}

void	exec_redir(t_tree *tree, t_envp *envp)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	if (redir->mode == O_RDONLY)
		redir_read(redir, envp);
	else
		redir_write(redir, envp);
}
