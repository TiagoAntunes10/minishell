/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conc_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:07:03 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/18 22:07:22 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*conc_str(char *s1, char *s2, char *s3, t_envp *envp)
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
