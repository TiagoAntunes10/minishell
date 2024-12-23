/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:44:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/23 12:21:36 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*expand_variable(char *str, t_envp *envp, int pos)
{
	t_envp	*envp_key;
	char	**arr;

	arr = str_divide(str, envp, pos);
	envp_key = search_envp(envp, arr[1]);
	free(str);
	if (envp_key == NULL)
	{
		if (ft_strncmp(arr[1], "?", lencmp(arr[1], "?")) == 0)
		{
			free(arr[1]);
			arr[1] = ft_itoa(g_exit_code);
		}
		else
			*(arr[1]) = 0;
	}
	else
	{
		free(arr[1]);
		arr[1] = NULL;
		arr[1] = ft_substr(envp_key->value, 0, ft_strlen(envp_key->value));
	}
	str = conc_str(arr, envp);
	clear_arr(arr);
	return (str);
}

static int	find_dolla(char *str)
{
	int	pos;

	pos = 0;
	if (*str == '$')
		return (pos);
	while (*str != 0)
	{
		if (*str == '$')
			return (pos);
		pos++;
		str++;
	}
	return (-1);
}

static int	expand_str(char **str, t_envp *envp, int pos)
{
	int	pos2;

	if (*(*str + pos + 1) != 0 && *(*str + pos + 1) != '"')
	{
		if (ft_strlen(*str + pos) > 1 && *(*str + pos + 1) != ' ')
			*str = expand_variable(*str, envp, pos);
	}
	if (**str == 0 || *(*str + pos) == 0)
		return (-1);
	pos2 = find_dolla(*str + pos + 1);
	if (pos2 == -1)
		pos = pos2;
	else
		pos += pos2 + 1;
	return (pos);
}

void	check_dolla(char **origin, t_envp *envp)
{
	int	pos;

	if (**origin != '\'')
	{
		pos = find_dolla(*origin);
		while (pos != -1)
			pos = expand_str(origin, envp, pos);
	}
}
