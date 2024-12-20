/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:44:56 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/20 17:31:07 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

extern int	g_exit_code;

static char	*get_key(char *str)
{
	char	*key;
	int		size;

	if (*str == '\\')
		return (NULL);
	str++;
	if (*str == '?')
		return (ft_substr(str, 0, 1));
	size = 0;
	while (str[size] != 0 && str[size] != ' ')
		size++;
	key = ft_substr(str, 0, size);
	return (key);
}

static char	*expand_variable(char *str, t_envp *envp, int pos)
{
	char	*prefix;
	char	*suffix;
	char	*key;
	t_envp	*envp_key;

	key = get_key(str + pos);
	prefix = ft_substr(str, 0, pos);
	suffix = ft_substr(str, pos + ft_strlen(key) + 1, 
					ft_strlen(str + pos + ft_strlen(key) + 1));
	envp_key = search_envp(envp, key);
	free(str);
	if (ft_strncmp(key, "?", lencmp(key, "?")) == 0)
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
		if (*(str + 1) == '$' && *str == '\\')
			return (pos);
		else if (*str == '$')
			return (pos);
		pos++;
		str++;
	}
	return (-1);
}

static int	expand_str(char **str, t_envp *envp, int pos)
{
	int	pos2;
	
	*str = expand_variable(*str, envp, pos);
	if (**str == 0 || *(*str + pos) == 0)
		return (-1);
	pos2 = find_dolla(*str + pos + 1);
	if (pos2 == -1)
		pos = pos2;
	else
		pos += pos2 + 1;
	return (pos);
}

void	check_dolla(t_cmd *cmd, t_envp *envp)
{
	int	pos;
	int	i;

	if (*(cmd->cmd) != '\'')
	{
		pos = find_dolla(cmd->cmd);
		while (pos != -1)
			pos = expand_str(&cmd->cmd, envp, pos);
	}
	i = 0;
	while (cmd->opt[i] != NULL)
	{
		if (*(cmd->opt[i]) != '\'')
		{
			pos = find_dolla(cmd->opt[i]);
			while (pos != -1)
				pos = expand_str(&cmd->opt[i], envp, pos);
		}
		i++;
	}
}
