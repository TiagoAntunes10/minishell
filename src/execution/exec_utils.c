/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/14 21:28:44 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Reduce number of lines
void	exec_pipe(t_tree *tree, int fd)
{
	int		*inp_pipe;
	int		id;
	t_pipe	*pipe_node;
	int		status;

	id = fork();
	if (id == -1)
		return ;
	else if (id == 0)
	{
		pipe_node = (t_pipe *) tree;
		// TODO: Not sure if this should exit
		if (pipe(inp_pipe) == -1)
			exit(1);
		id = fork();
		if (id == -1)
			exit(1);
		else if (id == 0)
		{
			if (dup2(inp_pipe[1], 1) == -1)
			{
				close(inp_pipe[0]);
				close(inp_pipe[1]);
				exit(1);
			}
			close(inp_pipe[1]);
			execution(pipe_node->left, 1);
		}
		waitpid(-1, &status, WNOHANG);
		close(inp_pipe[1]);
		if (fd == 1 || fd == -1)
		{
			if (dup2(inp_pipe[0], 0) == -1)
			{
				close(inp_pipe[0]);
				// TODO: Check if I should close this end of the pipe here
				if (fd == 1)
					close(fd);
				exit(1);
			}
			close(inp_pipe[0]);
		}
		execution(pipe_node->right, 0);
	}
	waitpid(-1, &status, WNOHANG);
	return ;
}

// TODO: Reduce number of lines
void	exec_delim(t_tree *tree, int fd)
{
	t_delim	*delim;
	char	*line;
	int		*inp_pipe;
	int		id;

	delim = (t_delim *) tree;
	line = NULL;
	if (pipe(inp_pipe) == -1)
		exit(1);
	id = fork();
	if (id == -1)
		exit(1);
	else if (id == 0)
	{
		close(inp_pipe[0]);
		line = get_next_line(0);
		while (ft_strncmp(delim->delim, line, ft_strlen(line)) != 0)
		{
			// TODO: Not sure if I should handle the errors in this way
			if (write(inp_pipe[1], line, ft_strlen(line)) == -1)
				exit(errno);
			free(line);
			line = get_next_line(0);
		}
		close(inp_pipe[1]);
		exit(0);
	}
	waitpid(-1, &id, WNOHANG);
	close(inp_pipe[1]);
	if (dup2(inp_pipe[0], 0) == -1)
	{
		close(inp_pipe[0]);
		exit(1);
	}
	close(inp_pipe[0]);
	execution(delim->right, 0);
}

void	exec_list(t_tree *tree, int fd)
{
	t_lst	*lst;

	lst = (t_lst *) tree;
	execution(lst->left, fd);
	execution(lst->right, fd);
}

// TODO: Reduce number of lines
void	exec_redir(t_tree *tree, int fd)
{
	t_redir	*redir;
	int		redir_fd;
	int		id;

	redir = (t_redir *) tree;
	id = fork();
	if (id == -1)
		exit(1);
	else if (id == 0)
	{
		if (redir->mode == O_RDONLY)
		{
			// TODO: Check if this error should be handled in this way
			if (access(redir->file, F_OK | R_OK) == -1)
				exit(errno);
			// TODO: Check if this error should be handled in this way
			redir_fd = open(redir->file, redir->mode);
			if (redir_fd == -1)
				exit(errno);
			if (dup2(redir_fd, 0) == -1)
			{
				close(redir_fd);
				exit(errno);
			}
			close(redir_fd);
			execution(redir->right, 0);
		}
		else
		{
			redir_fd = open(redir->file, redir->mode, 0755);
			// TODO: Check if this error should be handled in this way
			if (redir_fd == -1)
				exit(errno);
			// TODO: Check if this error should be handled in this way
			if (dup2(redir_fd, 1) == -1)
			{
				close(redir_fd);
				exit(errno);
			}
			close(redir_fd);
			execution(redir->right, 1);
		}
	}
}
