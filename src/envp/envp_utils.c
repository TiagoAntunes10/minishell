/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:57:26 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/30 17:07:14 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// TODO: Move to another file
static char	**envp_split(char *str, t_envp *envp)
{
	char	**key_value;
	int		size;

	key_value = (char **) safe_alloc(sizeof(*key_value), 3, NULL, NULL);
	size = 0;
	while (str[size] != '=')
		size++;
	key_value[0] = malloc(size + 1);
	if (key_value[0] == NULL)
	{
		free(key_value);
		exit_failure(NULL, -1, envp);
	}
	ft_strlcat(key_value[0], str, size + 1);
	str += size + 1;
	size = ft_strlen(str);
	key_value[1] = malloc(size + 1);
	if (key_value[1] == NULL)
	{
		clear_arr(key_value);
		exit_failure(NULL, -1, envp);
	}
	ft_strlcat(key_value[1], str, size + 1);
	key_value[2] = NULL;
	return (key_value);
}

static t_envp	*create_lst(char *envp)
{
	t_envp	*envp_lst;
	char	**key_value;
	int		size;

	key_value = envp_split(envp, NULL);
	envp_lst = (t_envp *) safe_alloc(sizeof(*envp_lst), 1, NULL, NULL);
	size = ft_strlen(key_value[0]) + 1;
	envp_lst->key = (char *) safe_alloc(size, 1, NULL, envp_lst);
	ft_strlcat(envp_lst->key, key_value[0], size);
	size = ft_strlen(key_value[1]) + 1;
	envp_lst->value = (char *) safe_alloc(size, 1, NULL, envp_lst);
	ft_strlcat(envp_lst->value, key_value[1], size);
	envp_lst->next = NULL;
	envp_lst->root = NULL;
	clear_arr(key_value);
	return (envp_lst);
}

static void	add_envp(char *envp, t_envp *envp_lst)
{
	t_envp	*envp_node;
	char	**key_value;
	int		size;

	key_value = envp_split(envp, envp_lst);
	envp_node = (t_envp *) safe_alloc(sizeof(*envp_node), 1, NULL, envp_lst);
	size = ft_strlen(key_value[0]) + 1;
	envp_node->key = (char *) safe_alloc(size, 1, NULL, envp_lst);
	ft_strlcat(envp_node->key, key_value[0], size);
	size = ft_strlen(key_value[1]) + 1;
	envp_node->value = (char *) safe_alloc(size, 1, NULL, envp_lst);
	ft_strlcat(envp_node->value, key_value[1], size);
	while (envp_lst->next != NULL)
		envp_lst = envp_lst->next;
	envp_lst->next = envp_node;
	envp_node->next = NULL;
	envp_node->root = NULL;
	clear_arr(key_value);
}

t_envp	*arr_to_lst(char **envp)
{
	t_envp	*envp_lst;

	envp_lst = create_lst(*envp);
	while (*(++envp) != NULL)
		add_envp(*envp, envp_lst);
	return (envp_lst);
}

static int	lst_len(t_envp *envp)
{
	int	len;

	len = 0;
	while (envp != NULL)
	{
		envp = envp->next;
		len++;
	}
	return (len);
}

char	**lst_to_arr(t_envp *envp)
{
	char	**arr;
	int		size;
	int		i;

	arr = (char **) safe_alloc(lst_len(envp) + 1, sizeof(char *), NULL, envp);
	i = 0;
	while (envp != NULL)
	{
		size = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
		arr[i] = malloc(size);
		if (arr[i] == NULL)
		{
			clear_arr(arr);
			exit_failure(NULL, -1, envp);
		}
		ft_strlcat(arr[i], envp->key, ft_strlen(envp->key) + 1);
		ft_strlcat(arr[i], "=", ft_strlen(envp->key) + 2);
		ft_strlcat(arr[i++], envp->value, size);
	}
	return (arr);
}
