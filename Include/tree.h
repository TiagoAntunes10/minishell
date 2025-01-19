/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:15:44 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/18 21:10:04 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_tree
{
	int	type;
}				t_tree;

typedef struct s_pipe
{
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_pipe;

typedef struct s_delim
{
	int				type;
	int				fd;
	char			*delim;
	struct s_tree	*right;
}				t_delim;

typedef struct s_cmd
{
	int		type;
	char	*cmd;
	char	**opt;
	int		num_opt;
}				t_cmd;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				mode;
	struct s_tree	*right;
}				t_redir;

#endif
