/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:52:56 by tialbert          #+#    #+#             */
/*   Updated: 2024/09/28 11:01:46 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

static int	check_pipe(char **tokens)
{
	char	**token_arr;
	int		count;

	token_arr = tokens;
	token_arr++;
	count = 0;
	while (*token_arr != NULL)
	{
		if (ft_strncmp(*token_arr, "|", 1) == 0)
			count++;
		token_arr++;
	}
	return (count);
}

static t_tokens	*first_node()
{
	t_tokens	*lst;

	lst = malloc(sizeof(t_tokens));
	//TODO; Add function that exits program
	if (lst == NULL)
		return (NULL);
	lst->cmd = NULL;
	lst->infile = NULL;
	lst->options = NULL;
	lst->outfile = NULL;
	lst->priority = 0;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

static void	add_node(t_tokens *lst)
{
	t_tokens	*next_node;
	t_tokens	*lst_cpy;

	next_node = malloc(sizeof(t_tokens));
	//TODO; Add function that exits program
	if (next_node == NULL)
		return ;
	lst_cpy = lst;
	next_node->prev = lst;
	while (lst_cpy->next != NULL)
		lst_cpy = lst_cpy->next;
	lst_cpy->next = next_node;
	next_node->cmd = NULL;
	next_node->infile = NULL;
	next_node->options = NULL;
	next_node->outfile = NULL;
	next_node->priority = 0;
	next_node->next = NULL;
}

t_tokens	*create_lst(char **tokens)
{
	t_tokens	*token_lst;
	int			pipe_num;
	int			i;
	
	pipe_num = check_pipe(tokens);	
	token_lst = first_node();
	i = 0;
	while (i++ < pipe_num)
		add_node(token_lst);
	return (token_lst);	
}

int	lst_len(t_tokens *lst)
{
	t_tokens	*lst_cpy;
	int			len;

	lst_cpy = lst;
	len = 0;
	while (lst_cpy != NULL)
	{
		len++;
		lst_cpy = lst_cpy->next;
	}
	return (len);
}
