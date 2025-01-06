/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:13:03 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/03 16:25:46 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	get_full_str(t_cmd *cmd, t_envp *envp, int is_bt)
{
	int		i;

	i = 0;
	if (quotes_pairs(cmd->cmd, envp, is_bt) == -1)
		return (-1);
	cmd->cmd = clean_str(cmd->cmd, envp, 0);
	while (cmd->opt[i] != NULL)
	{
		if (quotes_pairs(cmd->opt[i], envp, is_bt) == -1)
			return (-1);
		cmd->opt[i] = clean_str(cmd->opt[i], envp, 0);
		i++;
	}
	return (0);
}

//NOTE: this function explicity only compares up to the size of the invalid
//tokens in order to prevent cases where multiple of the same input
//or erraneous input is given! PLEASE DO BE AWARE

int	is_redir_valid(char *file)
{
	char	**invalid;
	int		i;

	i = -1;
	invalid = (char *[]){"<<", ">>", "<", ">", "|", "||", NULL};
	if (file == 0 || *file == '\n' || *file == '\0')
	{
		stat_ret(RED REDIR_ERR RST, 2);
		return (0);
	}
	while (invalid[++i])
	{
		if (!ft_strncmp(file, invalid[i], ft_strlen(invalid[i])))
		{
			ft_putstr_fd(RED REDIR_TOK, 2);
			stat_ret(invalid[i], 2);
			ft_putstr_fd("\'\n"RST, 2);
			return (0);
		}
	}
	return (1);
}

int	is_bt(t_cmd *cmd, t_envp *envp)
{
	char	**bts;
	int		i;

	(void)envp;
	bts = (char *[]){"echo", "pwd", "export", "unset", "env", "cd", NULL};
	i = -1;
	while (bts[++i])
		if (ft_strncmp(cmd->cmd, bts[i], lencmp(cmd->cmd, bts[i])) == 0)
			return (i);
	return (0);
}

int	bt_exec(t_tree *tree, t_envp *envp, int bt)
{
	t_cmd	*cmd;
	int		(**bt_func)(t_cmd *, t_envp *);

	bt_func = (int (*[])(t_cmd *, t_envp *)){ft_echo, ft_pwd, ft_export,
		ft_unset, ft_env, ft_cd, NULL};
	cmd = (t_cmd *)tree;
	if (bt)
		return (bt_func[bt](cmd, envp));
	return (0);
}
