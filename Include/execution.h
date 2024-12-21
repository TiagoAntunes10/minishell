/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:42:28 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/21 15:50:16 by tialbert         ###   ########.fr       */
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
void	*ft_freematrix(char **matrix);
void	ft_free(void *ptr);

//builtins

int		ft_unset(t_cmd *cmd, t_envp *envp);
int		ft_export(t_cmd *cmd, t_envp *envp);
int		ft_cd(t_cmd *cmd, t_envp *envp);
int		ft_env(t_cmd *cmd, t_envp *envp);
int		ft_echo(t_cmd *cmd, t_envp *envp);
int		ft_pwd(void);
void	ft_exit(t_tree *tree, t_envp *envp);

//useful functions

size_t	ft_strcspn(const char *str, const char *reject);
int		export_env(char *var, t_envp *envp);

#endif
