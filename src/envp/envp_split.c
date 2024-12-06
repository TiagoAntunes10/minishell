/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:48:09 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/04 22:51:25 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*empty_alloc(int size)
{
	char	*str;

	str = malloc(size);
	if (str == NULL)
		return (NULL);
	bzero(str, size);
	return (str);
}

char	**envp_split(char *str, t_envp *envp)
{
	char	**key_value;
	int		size;

	key_value = (char **) safe_alloc(sizeof(*key_value), 3, NULL, NULL);
	size = 0;
	while (str[size] != '=')
		size++;
	key_value[0] = empty_alloc(size + 1);
	if (key_value[0] == NULL)
	{
		free(key_value);
		exit_failure(NULL, -1, envp);
	}
	ft_strlcat(key_value[0], str, size + 1);
	str += size + 1;
	size = ft_strlen(str);
	key_value[1] = empty_alloc(size + 1);
	if (key_value[1] == NULL)
	{
		clear_arr(key_value);
		exit_failure(NULL, -1, envp);
	}
	ft_strlcat(key_value[1], str, size + 1);
	key_value[2] = NULL;
	return (key_value);
}
