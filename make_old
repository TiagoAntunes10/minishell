PRE = ./
INCLUDE = ./Include
FUNCTION = ./libft
MLX = ./minilibx-linux
BONUS = ./bonus/

# SOURCE = fractol.c errors.c ft_atod.c mlx_utils.c mlx_hooks.c \
# 		utils.c mandel.c julia.c

# SOURCE_BON = fractol_bonus.c errors_bonus.c ft_atod.c mlx_utils.c mlx_hooks.c \
# 		utils.c mandel_bonus.c julia_bonus.c utils_bonus.c tricorn.c

SOURCE_TEST = tests.c tokeniser.c cleanup.c lst_op.c tokeniser_utils.c

SOURCES = ${addprefix $(PRE), $(SOURCE)}
SOURCES_BON = ${addprefix $(PRE), $(SOURCE_BON)}
SOURCES_TEST = ${addprefix $(PRE), $(SOURCE_TEST)}

NAME = fractol
NAME_BONUS = fractol_bonus
NAME_TEST = tests
LIB = $(FUNCTION)/libftprintf.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g 

OBJ = $(SOURCES:.c=.o)
OBJ_BON = $(SOURCES_BON:.c=.o)
OBJ_TEST = $(SOURCES_TEST:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX_COM)
	cc $(FLAGS) -o $@ $^ $(MLX_FLAGS)

$(LIB):
	$(MAKE) -C $(FUNCTION)

.c.o:
		$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BON) $(LIB) $(MLX_COM)
	cc $(FLAGS) -o $@ $^ $(MLX_FLAGS)

.c.o2:
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

test: $(NAME_TEST)

$(NAME_TEST): $(OBJ_TEST) $(LIB)
	cc $(FLAGS) -o $@ $^

clean: 
	rm -f $(OBJ) $(OBJ_BON) $(OBJ_TEST)
	$(MAKE) clean -C $(FUNCTION)
        
fclean: clean
	rm -f $(NAME) $(NAME_BONUS) $(NAME_TEST)
	$(MAKE) fclean -C $(FUNCTION)

re: fclean all
