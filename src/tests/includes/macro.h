/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:13:57 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/13 21:40:46 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H 
# define MACRO_H 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <assert.h>
#include <errno.h>

typedef struct s_envp {
	char			*key;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_cmd {
//	int		type;
	char	*cmd;
	char	**opt;
}				t_cmd;


//colour prints

# define RST "\e[0m"
# define ULI "\e[4m"
# define BLN "\e[5m"
# define BLK "\e[1;30m"
# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define YLW "\e[1;33m"
# define BLU  "\e[1;34m"
# define PRP "\e[1;35m"
# define CYN "\e[1;36m"
# define WHT "\e[1;37m"

//CD ERRORS

# define CD_NOT_FND "cd: No such file or directory\n"
# define CD_NO_PERM "cd: Permission denied\n"
# define CD_GEN_ERR "cd: Could not change directory\n"
# define CD_NOT_DIR "cd: File is not a directory\n"
# define CD_ERR_ARG "cd: Too many arguments\n"

//PWD ERRORS

# define PWD_ERR_ARG "pwd: Too many arguments\n"
# define PWD_NO_PRNT "pwd: could not print current directory\n"


//builtins

typedef int	(*t_builtin_fn[])(t_cmd *, t_envp *);

int		ft_unset(t_cmd *cmd, t_envp *envp);
int		ft_export(t_cmd *cmd, t_envp *envp);
int		ft_cd(t_cmd *cmd, t_envp *envp);
int		ft_env(t_cmd *cmd, t_envp *envp);
int		ft_echo(t_cmd *cmd, t_envp *envp);
int		ft_pwd(t_cmd *cmd, t_envp *envp);

//useful functions

size_t	ft_strcspn(const char *str, const char *reject);
int		export_env(char *var, t_envp *envp);

//test envp

t_envp	*search_envp(t_envp *head, char *var);
t_envp	*arr_to_lst(char **envp);
char	**lst_to_arr(t_envp *envp);

//signal

void	signal_parent(void);
void	signal_child(void);
void	signal_ignore(void);
//void	signal_heredoc(void);

#endif
