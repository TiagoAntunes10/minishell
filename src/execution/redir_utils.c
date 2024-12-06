/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:12:05 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/01 16:20:27 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Write errors with perror
void	redir_read(t_redir *redir, t_envp *envp)
{
	int		redir_fd;

	if (access(redir->file, F_OK | R_OK) == -1)
		exit(errno);
	redir_fd = open(redir->file, redir->mode);
	if (redir_fd == -1)
		exit(errno);
	if (dup2(redir_fd, 0) == -1)
	{
		close(redir_fd);
		exit(errno);
	}
	close(redir_fd);
	execution(redir->right, 0, envp);
	close(0);
}

void	redir_write(t_redir *redir, t_envp *envp)
{
	int		redir_fd;

	redir_fd = open(redir->file, redir->mode, 0755);
	if (redir_fd == -1)
		exit(errno);
	if (dup2(redir_fd, 1) == -1)
	{
		close(redir_fd);
		exit(errno);
	}
	close(redir_fd);
	execution(redir->right, 1, envp);
	close(1);
}
