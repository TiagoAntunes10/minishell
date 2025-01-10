/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:12:05 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/06 21:03:51 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_read(t_redir *redir, t_envp *envp)
{
	int	redir_fd;

	if (!is_redir_valid(redir->file))
		exit_failure(envp->root, NULL, envp);
	if (access(redir->file, F_OK | R_OK) == -1)
	{
		ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		stat_ret(": No such file or directory\n"RST, 1);
		exit_failure(envp->root, NULL, envp);
	}
	redir_fd = open(redir->file, redir->mode);
	if (redir_fd == -1)
		exit_failure(envp->root, NULL, envp);
	if (dup2(redir_fd, 0) == -1)
	{
		close(redir_fd);
		exit_failure(envp->root, NULL, envp);
	}
	close(redir_fd);
	execution(redir->right, 0, envp);
	close(0);
}

void	redir_write(t_redir *redir, t_envp *envp)
{
	int	redir_fd;

	if (!is_redir_valid(redir->file))
		exit_failure(envp->root, NULL, envp);
	redir_fd = open(redir->file, redir->mode, 0755);
	if (redir_fd == -1)
	{
		ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		stat_ret(": No such file or directory\n"RST, 1);
		exit_failure(envp->root, NULL, envp);
	}
	if (dup2(redir_fd, 1) == -1)
	{
		close(redir_fd);
		exit_failure(envp->root, NULL, envp);
	}
	close(redir_fd);
	execution(redir->right, 1, envp);
	close(1);
}
