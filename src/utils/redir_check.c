/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:59:55 by tialbert          #+#    #+#             */
/*   Updated: 2024/12/30 23:01:43 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	redir_check(char *input)
{
	if (*input != '<' && *input != '>'
		&& ft_strncmp(input, "<<", ft_strlen(input)) != 0
		&& ft_strncmp(input, ">>", ft_strlen(input)) != 0)
		return (0);
	return (1);
}
