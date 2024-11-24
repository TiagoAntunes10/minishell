/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:15:44 by tialbert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/12 22:21:17 by tialbert         ###   ########.fr       */
=======
/*   Updated: 2024/11/17 18:01:25 by tialbert         ###   ########.fr       */
>>>>>>> 91d655cd368eec5976dfca42dd733e0176863e75
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_tree {
	int	type;
}				t_tree;

typedef struct s_pipe {
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_pipe;

<<<<<<< HEAD
typedef struct s_lst {
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_lst;

=======
>>>>>>> 91d655cd368eec5976dfca42dd733e0176863e75
typedef struct s_delim {
	int				type;
	char			*delim;
	struct s_tree	*right;
}				t_delim;

typedef struct s_cmd {
	int		type;
	char	*cmd;
	char	**opt;
}				t_cmd;

typedef struct s_redir {
	int				type;
	char			*file;
	int				mode;
	struct s_tree	*right;
}				t_redir;

#endif
