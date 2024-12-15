/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:13:57 by rapcampo          #+#    #+#             */
/*   Updated: 2024/11/13 21:40:46 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H 
# define MACRO_H 

//colour prints

# define RST "\e[0m"
# define ULI "\e[4m"
# define BLN "\e[5m"
# define BLK "\e[1;30m"
# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define YLW "\e[1;33m"
# define BLU  "\e[1;34m"
# define PRP "\e[1;35m"
# define CYN "\e[1;36m"
# define WHT "\e[1;37m"

//CD ERRORS

# define CD_NOT_FND "cd: No such file or directory\n"
# define CD_NO_PERM "cd: Permission denied\n"
# define CD_GEN_ERR "cd: Could not change directory\n"
# define CD_NOT_DIR "cd: File is not a directory\n"
# define CD_ERR_ARG "cd: Too many arguments\n"

//PWD ERRORS

# define PWD_ERR_ARG "pwd: Too many arguments\n"
# define PWD_NO_PRNT "pwd: could not print current directory\n"

//ECHO ERRORS


//Prompt

# define LOWER_PROMPT "\e[1;35mMinishell $->\e[0m"

#endif
