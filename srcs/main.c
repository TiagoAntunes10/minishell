/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:12 by tialbert          #+#    #+#             */
/*   Updated: 2024/10/17 21:46:54 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

//TODO: Verify if fd 1 is a terminal (that should be the standard)
int	main(void)
{
	char		*input;
	t_tokens	*tokens_lst;

	while (check_end() != 0)
	{
		input = readline(get_prompt());
		// TODO: create signal handling
		if (signal != 0)
			handle_signal(signal);
		if (input != NULL)
		{
			tokens_lst = tokenization(input);
			free(input);
			execution(tokens_lst);
			clear_lst(tokens_lst);
		}
	}
}
