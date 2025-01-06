BUILTIN = ./src/builtin/
CLEANUP = ./src/cleanup/
ENVP = ./src/envp/
EXEC = ./src/execution/
MEM = ./src/mem_alloc/
PARSER = ./src/parser/
SIG = ./src/signal/
UTILS = ./src/utils/
INCLUDE = ./Include
FUNCTION = ./libft
PRE = ./src/

BUILTIN_SOURCE = cmd_cd.c cmd_echo.c cmd_env.c cmd_export.c cmd_pwd.c \
				 cmd_unset.c cmd_exit.c
CLEANUP_SOURCE = cleanup.c tree_cleanup.c
ENVP_SOURCE = envp_search.c envp_split.c envp_utils.c env_shlvl.c
EXEC_SOURCE = distribution.c exec_utils.c pipe_utils.c redir_utils.c \
			  std_cmd.c expander.c quotes.c bt_logic.c
MEM_SOURCE = safe_alloc.c
PARSER_SOURCE = node_create.c node_org.c tokeniser.c tokeniser_utils.c
SIG_SOURCE = handlers.c signal_sorting.c
UTILS_SOURCE = tree_utils.c ft_strcspn.c lencmp.c conc_str.c stat_ret.c \
			   export_identifiers.c end_heredoc.c redir_check.c \
			   remove_quotes.c ft_freematrix.c parser_utils.c
SOURCE = main.c

BUILTIN_SOURCES = ${addprefix $(BUILTIN), $(BUILTIN_SOURCE)}
CLEANUP_SOURCES = ${addprefix $(CLEANUP), $(CLEANUP_SOURCE)}
ENVP_SOURCES = ${addprefix $(ENVP), $(ENVP_SOURCE)}
EXEC_SOURCES = ${addprefix $(EXEC), $(EXEC_SOURCE)}
MEM_SOURCES = ${addprefix $(MEM), $(MEM_SOURCE)}
PARSER_SOURCES = ${addprefix $(PARSER), $(PARSER_SOURCE)}
SIG_SOURCES = ${addprefix $(SIG), $(SIG_SOURCE)}
UTILS_SOURCES = ${addprefix $(UTILS), $(UTILS_SOURCE)}
SOURCES = ${addprefix $(PRE), $(SOURCE)}

NAME = minishell
LIB = $(FUNCTION)/libftprintf.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RD_LINE_FLAG = -lreadline

BUILTIN_OBJ = $(BUILTIN_SOURCES:.c=.o)
CLEANUP_OBJ = $(CLEANUP_SOURCES:.c=.o)
ENVP_OBJ = $(ENVP_SOURCES:.c=.o)
EXEC_OBJ = $(EXEC_SOURCES:.c=.o)
MEM_OBJ = $(MEM_SOURCES:.c=.o)
PARSER_OBJ = $(PARSER_SOURCES:.c=.o)
SIG_OBJ = $(SIG_SOURCES:.c=.o)
UTILS_OBJ = $(UTILS_SOURCES:.c=.o)
OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(BUILTIN_OBJ) $(CLEANUP_OBJ) $(ENVP_OBJ) $(EXEC_OBJ) $(MEM_OBJ) \
	$(PARSER_OBJ) $(SIG_OBJ) $(UTILS_OBJ) $(OBJ) $(LIB)
	cc $(FLAGS) -o $@ $^ $(RD_LINE_FLAG)

$(LIB):
	$(MAKE) -C $(FUNCTION)

.c.o:
		$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

clean: 
	rm -f $(BUILTIN_OBJ) $(CLEANUP_OBJ) $(ENVP_OBJ) $(EXEC_OBJ) $(MEM_OBJ) \
	$(PARSER_OBJ) $(SIG_OBJ) $(UTILS_OBJ) $(OBJ)
	$(MAKE) clean -C $(FUNCTION)
        
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(FUNCTION)

re: fclean all

.PHONY: all clean fclean re
