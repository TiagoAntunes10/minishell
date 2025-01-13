/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:34:49 by rapcampo          #+#    #+#             */
/*   Updated: 2025/01/12 20:59:19 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//NOTE: bash treats multiple args as different envs to be exported, therefore
//all args should just contain NAME or NAME[=VALUE] format. VALUE can contain
//quotation marks. 
//In case NAME is stored as a temp variable, without VALUE, ENV will not print
//but EXPORT will print it, and case export NAME[=VALUE] is called again
//VALUE will be appended to the variable and ENV will print it.

//TODO: create an env add function to append an item to the list
//TODO: env search for value appending
//TODO: all variables printed with "declare -x" string prefacing it and VALUE
//must be printed with quotation marks
//TODO: value appending should work with existing values

static	void	export_print(t_envp *envp)
{
	char	*dec;
	t_envp	*head;

	dec = "declare -x";
	head = envp->next;
	while (head)
	{
		if (!ft_strncmp(head->value, "", 1))
		{
			if (printf("%s %s\n", dec, head->key) == -1)
				return ;
		}
		else
		{
			if (printf("%s %s=\"%s\"\n", dec, head->key, head->value) == -1)
				return ;
		}
		head = head->next;
	}
}

static	void	append_node(t_envp *head, t_envp *new_node)
{
	t_envp	*temp;

	if (!head || !new_node)
		return ;
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

int	node_check(char *key, char *value, t_envp *envp, int a_flag)
{
	t_envp	*node;

	node = search_envp(envp, key);
	if (!node)
	{
		node = ft_calloc(1, sizeof(*envp));
		if (!node)
			return (-1);
		node->key = key;
		node->value = value;
		node->next = NULL;
		node->root = NULL;
		node->input_arr = NULL;
		append_node(envp, node);
	}
	else
	{
		free(key);
		to_append_or_not_to_append(value, node, a_flag);
	}
	return (0);
}

int	export_env(char *var, t_envp *envp)
{
	char	*key;
	char	*value;
	int		i;

	i = ft_strcspn(var, "=");
	if (var[i - 1] == '+')
		return (extract_appendage(var, envp, i));
	key = ft_substr(var, 0, i);
	if (!key)
		return (-1);
	value = ft_substr(var, i + 1, ft_strlen(var + i));
	if (!value)
	{
		free(key);
		return (-1);
	}
	if (node_check(key, value, envp, 0) == -1)
	{
		free(key);
		free(value);
		return (-1);
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_envp *envp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!cmd->opt[1])
		export_print(envp);
	while (cmd->opt[++i])
	{
		if (!is_valid_identifier(cmd->opt[i]))
		{
			ft_putstr_fd(RED"export: ", 2);
			ft_putstr_fd(cmd->opt[i], 2);
			ft_putstr_fd(INVAL_ID RST, 2);
			flag++;
		}
		else if ((export_env(cmd->opt[i], envp)) == -1)
			return (stat_ret(RED MEM_ALLOC RST, 126));
	}
	if (flag)
		return (stat_ret(NULL, 1));
	return (stat_ret(NULL, 0));
}
