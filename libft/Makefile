# ================================= Files ======================================

NAME	= libft.a
SOURCE	= $(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.c)) 
OBJS	= objs/*.o
DEPFLG	= -MP -MD

# ============================ Folder Structures ===============================

HEADERS		= ../includes/
SOURCE_DIR	= srcs/ctype srcs/list srcs/stdio srcs/stdlib srcs/string srcs/printf srcs/gnl
OBJS_DIR	= objs/

# ============================ Commands & Flags ===============================

CC			= cc
RM			= rm -rf
AR			= ar -rcs
FLAGS		= -Wall -Werror -Wextra -I$(HEADERS) #$(DEPFLG)
MAKE_FLAG	= --no-print-directory

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

vpath %.c $(SOURCE_DIR)

all: $(NAME)

$(NAME): $(OBJS)
#	echo "[$(PURPLE)$(BLINK)Compiling...$(RESET)] $(YELLOW)libft$(RESET)"
#	echo "[$(CYAN)$(BLINK)Linking...$(RESET)]"
	$(AR) $(NAME) $(OBJS)
	echo "\n*************************$(GREEN)$(BLINK)    [Libft Sucessfull!]    $(RESET)*************************\n"

$(OBJS): 
#	echo "[$(PURPLE)$(BLINK)Compiling...$(RESET)] $(YELLOW)sources$(RESET)"
	mkdir -p objs
	$(CC) $(FLAGS) -c $(SOURCE)
	mv *.o $(OBJS_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_DIR)
#	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Objects have been removed sucessfully$(RESET)    +++++++++++++++\n\n"

fclean: clean
	$(RM) $(NAME)
#	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Static library and programs removed successfully$(RESET)    +++++++++++++++\n\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
