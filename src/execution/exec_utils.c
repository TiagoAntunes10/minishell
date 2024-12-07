/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/07 23:11:34 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Write errors with perror
void	exec_pipe(t_tree *tree, int fd, t_envp *envp)
{
	int		inp_pipe[2];
	int		id;
	t_pipe	*pipe_node;
	int		status;

	pipe_node = (t_pipe *) tree;
	if (pipe(inp_pipe) == -1)
		exit(errno);
	id = fork();
	if (id == -1)
		exit(errno);
	else if (id == 0)
		child_pipe(pipe_node, envp, inp_pipe);
	waitpid(-1, &status, WNOHANG);
	close(inp_pipe[1]);
	if (fd == 1 || fd == -1)
		pipe_in_pipe(inp_pipe, fd);
	execution(pipe_node->right, 0, envp);
	close(0);
	exit(0);
}

static void	read_here_doc(char *delim, int inp_pipe)
{
	char	*line;
	
	printf("heredoc\n");
	line = get_next_line(0);
	printf("%s\n", line);
	while (ft_strncmp(delim, line, ft_strlen(line) - 1) != 0)
	{
		if (write(inp_pipe, line, ft_strlen(line)) == -1)
			exit(errno);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(inp_pipe);
}

void	exec_delim(t_tree *tree, t_envp *envp)
{
	t_delim	*delim;
	int		inp_pipe[2];

	delim = (t_delim *) tree;
	printf("delim1\n");
	if (pipe(inp_pipe) == -1)
		exit(errno);
	printf("delim2\n");
	read_here_doc(delim->delim, inp_pipe[1]);
	printf("delim3\n");
	if (dup2(inp_pipe[0], 0) == -1)
	{
		close(inp_pipe[0]);
		exit(errno);
	}
	close(inp_pipe[0]);
	execution(delim->right, 0, envp);
	close(0);
}

void	exec_redir(t_tree *tree, t_envp *envp)
{
	t_redir	*redir;
	int		id;

	redir = (t_redir *) tree;
	id = fork();
	if (id == -1)
		exit(errno);
	else if (id == 0)
	{
		if (redir->mode == O_RDONLY)
			redir_read(redir, envp);
		else
			redir_write(redir, envp);
	}
}
