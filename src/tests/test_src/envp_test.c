#include "macro.h"

t_envp	*search_envp(t_envp *head, char *var)
{
	t_envp	*curr;

	if (!head)
		return (NULL);
	curr = head;
	while (curr)
	{
		if (ft_strncmp(curr->key, var, ft_strlen(var)) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static char	**envp_split(char *str, t_envp *envp)
{
	char	**key_value;
	int		size;

	key_value = (char **)safe_alloc(sizeof(*key_value), 3, NULL);
	if (!key_value)
		return (NULL);
	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	key_value[0] = (char *)malloc(size + 1);
	if (key_value[0] == NULL)
	{
		ft_freematrix(key_value);
		return (NULL);
	}
	ft_strlcpy(key_value[0], str, size + 1);
	str += size + 1;
	size = ft_strlen(str);
	key_value[1] = (char *)malloc(size + 1);
	if (key_value[1] == NULL)
	{
		ft_freematrix(key_value);
		return (NULL);
	}
	ft_strlcpy(key_value[1], str, size + 1);
	key_value[2] = NULL;
	return (key_value);
}

static t_envp	*create_lst(char *envp)
{
	t_envp	*envp_lst;
	char	**key_value;
	int		size;

	key_value = envp_split(envp, NULL);
	envp_lst = (t_envp *) safe_alloc(sizeof(*envp_lst), 1, NULL);
	if (!envp_lst)
	{
		ft_freematrix(key_value);
		return (NULL);
	}
	size = ft_strlen(key_value[0]) + 1;
	envp_lst->key = safe_alloc(size, 1, envp_lst);
	if (!envp_lst->key)
	{
		clear_envp(envp_lst);
		return (NULL);
	}
	ft_strlcpy(envp_lst->key, key_value[0], size);
	size = ft_strlen(key_value[1]) + 1;
	envp_lst->value = (char *) safe_alloc(size, 1, envp_lst);
	if (!envp_lst->value)
	{
		clear_envp(envp_lst);
		return (NULL);
	}
	ft_strlcpy(envp_lst->value, key_value[1], size);
	envp_lst->next = NULL;
	if (key_value)
		ft_freematrix(key_value);
	return (envp_lst);
}

static void	add_envp(char *envp, t_envp *envp_lst)
{
	t_envp	*envp_node;
	char	**key_value;
	int		size;

	key_value = envp_split(envp, envp_lst);
	if (!key_value)
	{
		clear_envp(envp_lst);
		return ;
	}
	envp_node = (t_envp *) safe_alloc(sizeof(*envp_node), 1, envp_lst);
	if (!envp_node)
		return ;
	size = ft_strlen(key_value[0]) + 1;
	envp_node->key = (char *) safe_alloc(size, 1, envp_lst);
	if (!envp_node->key)
		return ;
	ft_strlcpy(envp_node->key, key_value[0], size);
	size = ft_strlen(key_value[1]) + 1;
	envp_node->value = (char *) safe_alloc(size, 1, envp_lst);
	if (!envp_node->value)
		return ;
	ft_strlcpy(envp_node->value, key_value[1], size);
	while (envp_lst->next != NULL)
		envp_lst = envp_lst->next;
	envp_lst->next = envp_node;
	envp_node->next = NULL;
	if (key_value)
		ft_freematrix(key_value);
}

t_envp	*arr_to_lst(char **envp)
{
	t_envp	*envp_lst;

	envp_lst = create_lst(*envp);
	if (!envp_lst)
		return (NULL);
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

char	**lst_to_arr(t_envp *head)
{
	char	**arr;
	int		size;
	int		i;
	t_envp *envp;

	envp = head;
	arr = malloc((lst_len(envp) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (envp != NULL)
	{
		size = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
		arr[i] = malloc(size);
		if (arr[i] == NULL)
		{
			ft_freematrix(arr);
			return (NULL);
		}
		ft_strlcat(arr[i], envp->key, ft_strlen(envp->key) + 1);
		ft_strlcat(arr[i], "=", ft_strlen(envp->key) + 2);
		ft_strlcat(arr[i++], envp->value, size);
	//	ft_stpcpy(arr[i], envp->key);
	//	ft_stpcpy(arr[i], "=");
	//	ft_stpcpy(arr[i], envp->value); 
		i++;
		envp = envp->next;
	}
	arr[i] = NULL;
	return (arr);
}
