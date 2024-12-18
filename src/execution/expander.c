/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:44:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/18 15:04:47 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static char	*get_key(char *str)
{
	char	*key;
	int		size;

	str++;
	if (*str == '?')
		return (ft_substr(str, 0, 1));
	size = 0;
	while (str[size] != 0 && str[size] != ' ')
		size++;
	key = ft_substr(str, 0, size);
	return (key);
}

static char	*conc_str(char *s1, char *s2, char *s3, t_envp *envp)
{
	int		size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s3) + ft_strlen(s2) + 1;
	str = (char *) safe_alloc(size, sizeof(*str), envp->root, envp);
	if (*s1 != 0)
		ft_strlcat(str, s1, ft_strlen(s1) + 1);
	if (s2 != NULL)
		ft_strlcat(str, s2, ft_strlen(str) + ft_strlen(s2) + 1);
	if (*s3 != 0)
		ft_strlcat(str, s3, ft_strlen(str) + ft_strlen(s3) + 1);
	return (str);
}

static char	*expand_variable(char *str, t_envp *envp, int pos)
{
	char	*prefix;
	char	*suffix;
	char	*key;
	t_envp	*envp_key;

	key = get_key(str + pos);
	prefix = ft_substr(str, 0, pos);
	suffix = ft_substr(str, pos + ft_strlen(key) + 1, ft_strlen(str + pos + ft_strlen(key) + 1));
	envp_key = search_envp(envp, key);
	free(str);
	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
	{
		free(key);
		key = ft_itoa(g_exit_code);
		str = conc_str(prefix, key, suffix, envp);
	}
	else if (envp_key != NULL)
		str = conc_str(prefix, envp_key->value, suffix, envp);
	else
		str = conc_str(prefix, NULL, suffix, envp);
	free(key);
	free(prefix);
	free(suffix);
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
		if (*(str + 1) == '$' && *str != '\\')
			return (pos + 1);
		pos++;
		str++;
	}
	return (-1);
}

void	check_dolla(t_cmd *cmd, t_envp *envp)
{
	int	pos;
	int	i;

	pos = find_dolla(cmd->cmd);
	if (pos != -1)
		cmd->cmd = expand_variable(cmd->cmd, envp, pos);
	i = 0;
	while (cmd->opt[i] != NULL)
	{
		pos = find_dolla(cmd->opt[i]);
		if (pos != -1)
			cmd->opt[i] = expand_variable(cmd->opt[i], envp, pos);
		i++;
	}
}
