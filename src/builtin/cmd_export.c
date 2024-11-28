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

#include "../../Include/minishell.h"
#include <stddef.h>

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

void	export_print(t_envp *envp)
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

void	append_node(t_envp *head, t_envp *new_node)
{
	t_envp	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	update_envp(char *value, t_envp *node)
{
	
}

void	export_env(char *var, t_envp *envp)
{
	t_envp	*node;
	size_t	key_size;
	size_t	val_size;
	char	*key;
	int		i;

	key_size = ft_strcspn(var, "=");
	key = ft_calloc(sizeof(char), key_size + 1);
	if (key == NULL)
		return ;
	ft_strlcpy(key, var, key_size);
	if (!(node = search_envp(envp, key)))
	{
		node = ft_calloc(sizeof(*envp), 1);
		node->key = key;
		node->value = NULL;
		node->next = NULL;
		append_node(envp, node);
	}
	if (ft_strchr(var, '=') != NULL)
		val_size = (ft_strlen(var) - 1) - key_size;
	else
		val_size = 0;



}

int	ft_export(t_cmd *cmd, t_envp *envp)
{
	int	i;

	i = 0;
	if (!cmd->opt[1])
		export_print(envp);
	while (cmd->opt[++i])
		export_env(cmd->opt[i], envp);
	return (EXIT_SUCCESS);
}
