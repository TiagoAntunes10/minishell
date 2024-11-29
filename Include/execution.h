/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:42:28 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/08 12:46:54 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <signal.h>

typedef	struct s_exec 
{
	int		exit_status;
	char	*cwd;
}			t_exec;

//concatanation
char	*ft_stpcpy(char *restrict dst, const char *restrict src);
void	*ft_mempcpy(void *dest, const void *src, size_t n);

//memory safety
void	ft_freematrix(char **matrix);
size_t	ft_strcspn(const char *str, const char *reject);

//builtins

int		ft_unset(t_cmd *cmd, t_envp *envp);
int		ft_export(t_cmd *cmd, t_envp *envp);
int		ft_cd(t_cmd *cmd, t_envp *envp);
int		ft_env(t_cmd *cmd, t_envp *envp);
int		ft_echo(t_cmd *cmd, t_envp *envp);
int		ft_pwd(t_cmd *cmd, t_envp *envp);

#endif
