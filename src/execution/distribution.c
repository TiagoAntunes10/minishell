/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:36:59 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/11 20:50:00 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static int is_builtin(char *name)
{
	char	**bt;
	int		i;

	bt = (char (*[])){"pwd", "echo", "env", "export",
		"unset", NULL};
	i = -1;
	while (bt[++i])
		if (name && !ft_strncmp(bt[i], name, ft_strlen(name)))
			return (1);
	return (0);
}

void	cmd_dist(t_tree *tree, t_envp *envp)
{
	t_cmd	*cmd;
	int		i;
	char	**bt_name;
	int		(**bt_func)(t_cmd *, t_envp *);

	cmd = (t_cmd *) tree;
	i = -1;
	bt_name = (char (*[])){"pwd",
		"echo", "env", "export", "unset", NULL};
	bt_func = (int (*[])(t_cmd *, t_envp *)){ft_pwd, ft_echo,
		ft_env, ft_export, ft_unset, NULL};
	if (!is_builtin(cmd->cmd))
		std_cmd(cmd, envp);
	else
		while (bt_name[++i])
			if (cmd->cmd && !ft_strncmp(bt_name[i], cmd->cmd, ft_strlen(cmd->cmd)))
				bt_func[i](cmd, envp);
}

static void	exec_tree(t_tree *tree, int fd, t_envp *envp)
{
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		exec_pipe(tree, fd, envp);
	else if (tree->type == DELIM)
		exec_delim(tree, envp);	
	else if (tree->type == REDIR)
		exec_redir(tree, envp);
	else if (tree->type == CMD)
		cmd_dist(tree, envp);
}

void	execution(t_tree *tree, int fd, t_envp *envp)
{
	t_cmd	*cmd;
	int		id;
	int		status;

	cmd = NULL;
	if (tree->type == CMD)
	{
		cmd = (t_cmd *) tree;
		if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
			ft_cd(cmd, envp);
		else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
			ft_exit(tree, envp);
	}
	signal_child();
	if (fd == -1)
	{
		id = fork();
		if (-1 == id)
			exit(1);
		else if (id == 0)
			exec_tree(tree, fd, envp);
		wait(&status);
	}
	else
		exec_tree(tree, fd, envp);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	signal_parent();
}
