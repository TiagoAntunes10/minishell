# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 09:38:27 by rapcampo          #+#    #+#              #
#    Updated: 2024/08/17 16:07:49 by rapcampo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Files ======================================

NAME	= minishell
LIBFT	= $(LIBFT_DIR)/libftprintf.a
DEPFLG	= -MP -MD
#FILES	= cmd_cd cmd_echo cmd_env cmd_exit cmd_export cmd_pwd cmd_unset main \
		  cleanup tree_cleanup envp_search envp_split envp_utils distribution \
		  exec_utils pipe_utils redir_utils std_cmd safe_alloc expander \
		  node_create node_org tokeniser tokeniser_utils handlers \
		  signal_sorting ft_freematrix ft_stpcpy ft_strcspn tree_utils
OBJS	= objs/*.o

# ============================ Folder Structures ===============================

HEADERS		= Include
SOURCE		= $(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.c)) 
SOURCE_DIR	= src src/builtin src/cleanup src/envp src/execution src/mem_alloc \
			  src/parser src/signal src/utils
LIBFT_DIR	= libft
OBJS_DIR	= objs

# ============================ Commands & Flags ===============================

CC			= cc
RM			= rm -rf
AR			= ar -rcs
FLAGS		= -g -O3 -fsanitize=thread #$(DEPFLG)
MAKE_FLAG	= --no-print-directory
LDLIBS		= -lreadline 

# =========================== Ansi Escape Codes ================================

ULINE	= \e[4m
BLINK	= \e[5m
BLACK 	= \e[1;30m
RED 	= \e[1;31m
GREEN 	= \e[1;32m
YELLOW 	= \e[1;33m
BLUE	= \e[1;34m
PURPLE 	= \e[1;35m
CYAN 	= \e[1;36m
WHITE 	= \e[1;37m
RESET	= \e[0m

# ================================ Rules =======================================
#vpath %.c $(SOURCE) $(addprefix $(SOURCE)/, $(SOURCE_DIR))
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	echo "[$(CYAN)$(BLINK)Linking...$(RESET)]"
	$(CC) $(FLAGS) $(LIBFT) -o $@ $^ $(LDLIBS)
	echo "\n*************************$(GREEN)$(BLINK)    [Compilation Sucessfull!]    $(RESET)*************************\n"

$(OBJS):
	echo "[$(PURPLE)$(BLINK)Compiling...$(RESET)] $(YELLOW)sources$(RESET)"
	mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) -c $(SOURCE) -I $(HEADERS)
	mv *.o $(OBJS_DIR)

$(LIBFT):
	echo "[$(PURPLE)$(BLINK)Compiling...$(RESET)] $(YELLOW)libft$(RESET)"
	make $(MAKE_FLAG) -C $(LIBFT_DIR)

clean:
	make clean $(MAKE_FLAG) -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	$(RM) $(OBJS_DIR)
	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Minishell Objects have been removed sucessfully$(RESET)    +++++++++++++++\n\n"

fclean: clean
	make fclean $(MAKE_FLAG) -C $(LIBFT_DIR)
	$(RM) $(NAME)
	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Minishell Static library and programs removed successfully$(RESET)    +++++++++++++++\n\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
