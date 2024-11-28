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

void	export_env(char *key, t_envp *envp)
{
	char	**keyvalue;
	size_t	size;

	if (!ft_strchr(key, '='))
		size = ft_strlen(key);
	else
	 size = ;
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
