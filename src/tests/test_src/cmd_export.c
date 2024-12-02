/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:34:49 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/26 00:57:09 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macro.h"

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
	head = envp;
	while (head)
	{
		if (!head->value)
			printf("%s %s\n", dec, envp->key);
		else
			printf("%s %s=\"%s\"\n", dec, envp->key, envp->value);
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

//strcspn will count the length until it finds '=', if it doesnt it will return
//the string length, which we will assume it is the key length.
//possibly need to free(var);

int	export_env(char *var, t_envp *envp)
{
	t_envp	*node;
	char	*key;
	char	*value;
	int		i;

	i = ft_strcspn(var, "=");
	if (!(key = ft_substr(var, 0, i)))
		return (-1);
	value = ft_strdup(var + (i + 1));
	if (!(node = search_envp(envp, key)))
	{
		if (!(node = ft_calloc(1, sizeof(*envp))))
			return (-1);
		node->key = key;
		node->value = value;
		append_node(envp, node);
	}
	else
	{
		free(key);
		free(node->value);
		node->value = value;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd, t_envp *envp)
{
	int	i;

	i = 0;
	if (!cmd->opt[1])
		export_print(envp);
	while (cmd->opt[++i])
		if ((export_env(cmd->opt[i], envp)) == -1)
			return (ft_putstr_fd("export: memory allocation failure", 2),
				STDERR_FILENO);
	return (EXIT_SUCCESS);
}
