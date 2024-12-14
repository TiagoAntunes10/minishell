/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:42:28 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/12 22:02:03 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "envp.h"
# include <stdlib.h>

//concatanation
char	*ft_stpcpy(char *restrict dst, const char *restrict src);
void	*ft_mempcpy(void *dest, const void *src, size_t n);

//memory safety
void	ft_freematrix(char **matrix);

//builtins

int		ft_unset(t_cmd *cmd, t_envp *envp);
int		ft_export(t_cmd *cmd, t_envp *envp);
int		ft_cd(t_cmd *cmd, t_envp *envp);
int		ft_env(t_cmd *cmd, t_envp *envp);
int		ft_echo(t_cmd *cmd, t_envp *envp);
int		ft_pwd(void);

//useful functions

size_t	ft_strcspn(const char *str, const char *reject);
int		export_env(char *var, t_envp *envp);

#endif
