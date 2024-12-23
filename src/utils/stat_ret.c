/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:50:36 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/22 14:15:15 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	stat_ret(char *msg, int ex_code)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	g_exit_code = ex_code;
	return (ex_code);
}
