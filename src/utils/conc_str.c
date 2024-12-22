/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conc_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/22 21:31:29 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*get_key(char *str)
{
	char	*key;
	int		size;

	str++;
	if (*str == '?')
		return (ft_substr(str, 0, 1));
	size = 0;
	while (str[size] != 0 && str[size] != ' ' && str[size] != '\''
		&& str[size] != '"')
		size++;
	key = ft_substr(str, 0, size);
	return (key);
}

char	**str_divide(char *str, t_envp *envp, int pos)
{
	char	*prefix;
	char	*suffix;
	char	*key;
	char	**arr;

	arr = (char **) safe_alloc(4, sizeof(char *), envp->root, envp);
	key = get_key(str + pos);
	prefix = ft_substr(str, 0, pos);
	suffix = ft_substr(str, pos + ft_strlen(key) + 1,
			ft_strlen(str + pos + ft_strlen(key) + 1));
	arr[0] = prefix;
	arr[1] = key;
	arr[2] = suffix;
	arr[3] = NULL;
	return (arr);
}

char	*conc_str(char **str_arr, t_envp *envp)
{
	int		len;
	char	*str;
	char	**arr_cpy;
	int		size;

	len = 0;
	size = 0;
	arr_cpy = str_arr;
	while (*arr_cpy != NULL)
	{
		size++;
		len += ft_strlen(*(arr_cpy++));
	}
	str = (char *) safe_alloc(len + 1, sizeof(*str), envp->root, envp);
	arr_cpy = str_arr;
	while ((size--) > 0)
	{
		if (*arr_cpy != NULL)
		{
			if (**arr_cpy != 0)
				ft_strlcat(str, *arr_cpy, ft_strlen(str) + ft_strlen(*arr_cpy) + 1);
		}
		arr_cpy++;
	}
	return (str);
}
