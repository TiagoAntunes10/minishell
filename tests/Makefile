PRE_PARSE = ../src/parser ../src/cleanup ../src/envp ../src/mem_alloc
PRE_UTILS = ../src/utils/
PRE_EXEC = ../src/execution/
PRE_BUILTIN = ../src/builtin/
PRE_EXP = ../src/execution/
INCLUDE = ../Include
FUNCTION = ../libft
TEST_PARSE = ./
TEST_EXEC = ./
TEST_EXP = ./

EXEC_SOURCE = exec_utils.c distribution.c std_cmd.c pipe_utils.c \
			  redir_utils.c quotes.c

BUILTIN_SOURCE = cmd_cd.c cmd_export.c cmd_exit.c cmd_env.c cmd_echo.c \
				 cmd_pwd.c cmd_unset.c

EXP_SOURCE = expander.c quotes.c

SOURCE_UTILS = tree_utils.c lencmp.c conc_str.c

SOURCE_PARSE = test_parse.c

SOURCE_EXEC = test_exec.c

SOURCE_EXP = test_expander.c

SOURCES = $(foreach dir, $(PRE_PARSE), $(wildcard $(dir)/*.c))
SOURCES_EXEC = ${addprefix $(PRE_EXEC), $(EXEC_SOURCE)}
SOURCES_BUILTIN = ${addprefix $(PRE_BUILTIN), $(BUILTIN_SOURCE)}
SOURCES_EXP = ${addprefix $(PRE_EXP), $(EXP_SOURCE)}
SOURCES_UTILS = ${addprefix $(PRE_UTILS), $(SOURCE_UTILS)}
SOURCES_TEST_PARSE = ${addprefix $(TEST_PARSE), $(SOURCE_PARSE)}
SOURCES_TEST_EXEC = ${addprefix $(TEST_EXEC), $(SOURCE_EXEC)}
SOURCES_TEST_EXP = ${addprefix $(TEST_EXP), $(SOURCE_EXP)}

NAME_TEST_PARSE = parse
NAME_TEST_EXEC = exec_test
NAME_TEST_EXP = expand
LIB = $(FUNCTION)/libftprintf.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g

OBJ = $(SOURCES:.c=.o)
OBJ_EXEC = $(SOURCES_EXEC:.c=.o)
OBJ_EXP = $(SOURCES_EXP:.c=.o)
OBJ_BUILTIN = $(SOURCES_BUILTIN:.c=.o)
OBJ_UTILS = $(SOURCES_UTILS:.c=.o)
OBJ_TEST_PARSE = $(SOURCES_TEST_PARSE:.c=.o)
OBJ_TEST_EXEC = $(SOURCES_TEST_EXEC:.c=.o)
OBJ_TEST_EXP = $(SOURCES_TEST_EXP:.c=.o)

test_parser: $(NAME_TEST_PARSE)

$(NAME_TEST_PARSE): $(OBJ) $(OBJ_UTILS) $(OBJ_TEST_PARSE) $(LIB)
	cc $(FLAGS) -o $@ $^

test_exec: $(NAME_TEST_EXEC)

$(NAME_TEST_EXEC): $(OBJ) $(OBJ_EXEC) $(OBJ_BUILTIN) $(OBJ_UTILS) \
	$(OBJ_TEST_EXEC) $(LIB)
	cc $(FLAGS) -o $@ $^

test_expand: $(NAME_TEST_EXP)

$(NAME_TEST_EXP): $(OBJ) $(OBJ_EXP) $(OBJ_UTILS) $(OBJ_TEST_EXP) $(LIB)
	cc $(FLAGS) -o $@ $^

$(LIB):
	$(MAKE) -C $(FUNCTION)

.c.o:
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

clean: 
	rm -f $(OBJ) $(OBJ_TEST_PARSE) $(OBJ_EXEC) $(OBJ_TEST_EXEC) $(OBJ_EXP) \
		$(OBJ_TEST_EXP) $(OBJ_UTILS) $(OBJ_BUILTIN)
	$(MAKE) clean -C $(FUNCTION)
        
fclean: clean
	rm -f $(NAME_TEST_PARSE) $(NAME_TEST_EXEC) $(NAME_TEST_EXP)
	$(MAKE) fclean -C $(FUNCTION)

re_test_parser: fclean test_parser

re_test_exec: fclean test_exec

re_test_expand: fclean test_expand
