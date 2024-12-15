/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:24:03 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/30 17:25:25 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	*ft_freematrix(char **matrix)
{
	int i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (NULL);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}
