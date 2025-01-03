/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/03 17:03:02 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exec_pipe(t_tree *tree, int fd, t_envp *envp)
{
	int		inp_pipe[2];
	// pid_t	id;
	t_pipe	*pipe_node;

	// (void)fd;
	pipe_node = (t_pipe *) tree;
	if (pipe(inp_pipe) == -1)
		exit_failure(envp->root, NULL, envp);
	// id = fork();
	// envp->child_proc++;
	// if (id == -1)
	// 	exit_failure(envp->root, inp_pipe, envp);
	// else if (id == 0)
	child_pipe(pipe_node, envp, inp_pipe);
	if (fd >= 1 || fd == -1)
		pipe_in_pipe(inp_pipe, fd, envp);
	execution(pipe_node->right, inp_pipe[1], envp);
	close(0);
	// exit_success(envp->root, 0, envp);
}

static void	read_here_doc(char *delim, int *inp_pipe, t_envp *envp)
{
	char	*line;

	if (!is_redir_valid(delim))
		exit_failure(envp->root, inp_pipe, envp);
	end_heredoc(envp, inp_pipe, 0);
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
	remove_quotes(&(delim->delim), 0);
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
	remove_quotes(&(redir->file), 0);
	if (redir->mode == O_RDONLY)
		redir_read(redir, envp);
	else
		redir_write(redir, envp);
}
