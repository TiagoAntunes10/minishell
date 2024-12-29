/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:13:57 by rapcampo          #+#    #+#             */
/*   Updated: 2024/12/22 10:48:59 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H 
# define MACRO_H 

//Linux key exit codes are as folows
//0: Success
//1: General error
//2: Missuse of builtins
//126: Command cannot execute: no perms or insuficient memory etc
//127: Command not found
//128: Invalid exit argument
//128 + signum: fatal signal, ex 137 = SIGKILL + 128
//130: control C termination SIGINT
//255: exit status out of range (valid is 0 to 254)

//colour prints

# define RST "\e[0m"
# define ULI "\e[4m"
# define BLN "\e[5m"
# define BLK "\e[1;30m"
# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define YLW "\e[1;33m"
# define BLU "\e[1;34m"
# define PRP "\e[1;35m"
# define CYN "\e[1;36m"
# define WHT "\e[1;37m"

//CD ERRORS

# define CD_NOT_FND "cd: No such file or directory\n"
# define CD_NO_PERM "cd: Permission denied\n"
# define CD_GEN_ERR "cd: Could not change directory\n"
# define CD_NOT_DIR "cd: File is not a directory\n"
# define CD_ERR_ARG "cd: Too many arguments\n"
# define CD_NO_HOME "cd: HOME not set\n"
# define CD_OLDPWD "cd: OLDPWD not set\n"

//PWD ERRORS

# define PWD_ERR_ARG "pwd: Too many arguments\n"
# define PWD_NO_PRNT "pwd: could not print current directory\n"

//ENV ERRORS

# define ENV_NOFILE "env: no such file or directory\n"

//EXPORT ERRORS

# define MEM_ALLOC "export: memory allocation failure\n"
# define INVAL_ID ": is an invalid identifier\n"

//PROMPT

# define UPPER_PROMPT "╭─"
# define LOWER_PROMPT "╰─\e[1;35mMinishell \e[1;33m$->\e[0m"

//HEREDOC ERRORS

# define SYNTAX_ERR "heredoc: syntax error near unexpected token `newline'\n"
# define HEREDOC_EOF "minishell: warning: here-doc delimited by end-of-file"

//EXIT ERRORS

# define EX_MANY_ARG "exit: too many arguments\n"
# define EX_ALPHA_ERR "exit: numeric argument required\n"

//PIPE ERRORS

# define PIPE_ERR "pipe: syntax error near unexpected token `|'\n"

//QUOTE ERRORS

# define QUOTE_ERR "quotes: unclosed quotes\n"

#endif
