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

# ================================ Macros ======================================

ST		= *************************
COMP	= Compiling...
CLN		= Minishell Objects have been removed sucessfully
FCLN	= Minishell programs removed successfully
SUCS	= [Compilation Sucessfull!]

# ================================ Rules =======================================

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	echo "[$(CYAN)$(BLINK)Linking...$(RESET)]"
	$(CC) $(FLAGS) $(LIBFT) -o $@ $^ $(LDLIBS)
	echo "\n$(ST)          $(GREEN)$(BLINK)$(SUCS)$(RESET)          $(ST)\n"

$(OBJS):
	echo "[$(PURPLE)$(BLINK)$(COMP)$(RESET)] $(YELLOW)sources$(RESET)"
	mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) -c $(SOURCE) -I $(HEADERS)
	mv *.o $(OBJS_DIR)

$(LIBFT):
	echo "[$(PURPLE)$(BLINK)$(COMP)$(RESET)] $(YELLOW)libft$(RESET)"
	make $(MAKE_FLAG) -C $(LIBFT_DIR)

clean:
	make clean $(MAKE_FLAG) -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	$(RM) $(OBJS_DIR)
	echo "\n\n$(ST)   $(ULINE)$(GREEN)$(CLN)$(RESET)   $(ST)\n\n"

fclean: clean
	make fclean $(MAKE_FLAG) -C $(LIBFT_DIR)
	$(RM) $(NAME)
	echo "\n\n$(ST)      $(ULINE)$(GREEN)$(FCLN)$(RESET)      $(ST)\n\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
