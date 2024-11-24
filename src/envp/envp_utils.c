/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:57:26 by tialbert          #+#    #+#             */
/*   Updated: 2024/11/24 18:01:19 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static t_envp	*create_lst(char *envp)
{
	t_envp	*envp_lst;
	char	**key_value;

	envp_lst = malloc(sizeof(*envp_lst));
	if (envp_lst == NULL)
		// TODO: Handle error
	key_value = ft_split(envp, '=');
	if (key_value == NULL)
		// TODO: Handle error
	envp_lst->key = malloc(ft_strlen(key_value[0] + 1));
	if (envp_lst->key == NULL)
		// TODO: Handle error
	envp_lst->value = malloc(ft_strlen(key_value[1] + 1));
	if (envp_lst->value == NULL)
		// TODO: Handle error
	ft_strlcat(envp_lst->key, key_value[0], ft_strlen(key_value[0]) + 1);
	ft_strlcat(envp_lst->value, key_value[1], ft_strlen(key_value[1]) + 1);
	envp_lst->next = NULL;
	return (envp_lst);
}

static void	add_envp(char *envp, t_envp *envp_lst)
{
	t_envp	*envp_node;
	char	**key_value;

	envp_node = malloc(sizeof(*envp_node));
	if (envp_node == NULL)
		// TODO: Handle error
	while (envp_lst->next != NULL)
		envp_lst = envp_lst->next;
	envp_lst->next = envp_node;
	key_value = ft_split(envp, '=');
	if (key_value == NULL)
		// TODO: Handle error
	envp_node->key = malloc(ft_strlen(key_value[0] + 1));
	if (envp_node->key == NULL)
		// TODO: Handle error
	envp_node->value = malloc(ft_strlen(key_value[1] + 1));
	if (envp_node->value == NULL)
		// TODO: Handle error
	ft_strlcat(envp_node->key, key_value[0], ft_strlen(key_value[0]) + 1);
	ft_strlcat(envp_node->value, key_value[1], ft_strlen(key_value[1]) + 1);
	envp_node->next = NULL;
}

t_envp	*arr_to_lst(char **envp)
{
	t_envp	*envp_lst;

	envp_lst = create_lst(*envp);
	while (++envp != NULL)
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

	arr = malloc((lst_len(envp) + 1) * sizeof(char *));
	if (arr == NULL)
		// TODO: Exit program
	i = 0;
	while (envp != NULL)
	{
		size = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
		arr[i] = malloc(size);
		if (arr[i] == NULL)
			// TODO: Clear array and exit program
		ft_strlcat(arr[i], envp->key, ft_strlen(envp->key) + 1);
		ft_strlcat(arr[i], ":", ft_strlen(envp->key) + 2);
		ft_strlcat(arr[i++], envp->value, size);
	}
	return (arr);
}
