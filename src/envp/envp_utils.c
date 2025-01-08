/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:57:26 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/03 17:13:33 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static t_envp	*create_lst(char *envp)
{
	t_envp	*envp_lst;
//	char	**key_value;
	int		size;

	(void)envp;
	size = 0;
//	key_value = envp_split(envp, NULL);
	envp_lst = (t_envp *) safe_alloc(sizeof(*envp_lst), 1, NULL, NULL);
//	size = ft_strlen(key_value[0]) + 1;
	envp_lst->key = (char *) safe_alloc(size, 1, NULL, envp_lst);
//	ft_strlcat(envp_lst->key, key_value[0], size);
//	size = ft_strlen(key_value[1]) + 1;
	size = ft_strlen("datanode") + 1;
	envp_lst->value = (char *) safe_alloc(size, 1, NULL, envp_lst);
//	ft_strlcat(envp_lst->value, key_value[1], size);
	ft_strlcat(envp_lst->value, "datanode", size);
	envp_lst->next = NULL;
	envp_lst->root = NULL;
	envp_lst->input_arr = NULL;
	envp_lst->child_proc = 0;
	envp_lst->fd_in = 0;
	envp_lst->fd_out = 0;
	envp_lst->id = -1;
//	clear_arr(key_value);
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
	envp_node->input_arr = NULL;
	envp_node->child_proc = 0;
	envp_node->fd_in = 0;
	envp_node->fd_out = 0;
	envp_node->id = -1;
	clear_arr(key_value);
}

t_envp	*arr_to_lst(char **envp)
{
	t_envp	*envp_lst;

	envp_lst = create_lst(*envp);
	while (*(envp) != NULL)
		add_envp(*envp++, envp_lst);
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
	t_envp	*envp_cpy;

	arr = (char **) safe_alloc(lst_len(envp) + 1, sizeof(char *), NULL, envp);
	i = 0;
	envp_cpy = envp;
	while (envp != NULL)
	{
		size = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
		arr[i] = malloc(size);
		bzero(arr[i], size);
		if (arr[i] == NULL)
		{
			clear_arr(arr);
			exit_failure(NULL, NULL, envp_cpy);
		}
		ft_strlcat(arr[i], envp->key, ft_strlen(envp->key) + 1);
		ft_strlcat(arr[i], "=", ft_strlen(envp->key) + 2);
		ft_strlcat(arr[i++], envp->value, size);
		envp = envp->next;
	}
	return (arr);
}
