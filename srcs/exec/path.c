/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:19:52 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/06 22:26:52 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: treating relative and absolute paths
//TODO: Finishing concatenation

char	*cat_path(char *tpath,char *path, char *name)
{
	ft_stpcpy(tpath, path);
	ft_stpcpy(tpath, "/");
	ft_stpcpy(tpath, name);
	return (tpath);
}

char	*ft_path(char *name)
{
	char	**path;
	int		i;
	struct stat	buffer = {0};

	path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path[++i])
	{
		char *tpath = ft_calloc(ft_strlen(path[i]) + ft_strlen(name) + 2, 1);
		if (!tpath)
			return (NULL);
		tpath = cat_path(tpath, path[i], name);
		if (stat(tpath, &buffer) == 0)
		{
			ft_freematrix(path);
			return (tpath);
		}
		if (tpath)
		{
			free(tpath);
			tpath = NULL;
		}
	}
	ft_freematrix(path);
	return (ft_strdup(name));
}
