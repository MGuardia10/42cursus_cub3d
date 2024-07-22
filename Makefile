################################################################################
# COMPILER OPTIONS
################################################################################

NAME		:=	cub3D
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -g3
INCLUDES	:=	-I libft/inc -I inc
RM			:=	rm -rf
MLXFLAGS	=	$(MLX) -Iinclude -ldl -lglfw -pthread -lm # LINUX
#MLXFLAGS	=	$(MLX) -lglfw -L ~/.brew/Cellar/glfw/3.4/lib # MACOS

# COLORS
RED		:=		\033[91;1m
GREEN	:=		\033[92;1m
YELLOW	:=		\033[93;1m
BLUE	:=		\033[94;1m
PINK	:=		\033[95;1m
CLEAR	:=		\033[0m

################################################################################
# SOURCE FILES
################################################################################

# LIBFT
LIBFT		:=	libft/libft.a

# MLX
MLX_BUILD	:= mlx/build
MLX			:=	mlx/build/libmlx42.a

# VPATH
VPATH		:=	src:src/parsing \
				src:src/raycasting \
				src:src/movement

# SOURCE
SRC			:=	main.c

# PARSING
PARSING		:=	init_game.c \
				errors.c \
				colors.c \
				textures.c \
				map.c \
				limits.c \
				clean.c \
				utils.c

# RAYCASTING
RAYCASTING 	:=	castrays.c \
				render.c \
				init.c \
				texture.c \
				minimap.c

MOVEMENT	:=	p_movement.c \
				key_managment.c

# OBJECTS
OBJ_DIR		:=	objs/
OBJ_FILES	=	$(SRC:%.c=$(OBJ_DIR)%.o) \
				$(PARSING:%.c=$(OBJ_DIR)%.o) \
				$(RAYCASTING:%.c=$(OBJ_DIR)%.o) \
				$(MOVEMENT:%.c=$(OBJ_DIR)%.o)

################################################################################
# MAKEFILE RULES
################################################################################


all: libmlx $(NAME)

libmlx:
	@if [ ! -e $(MLX_BUILD) ]; then \
		echo "$(BLUE)Compiling mlx.$(CLEAR)"; \
		cmake ./mlx -B ./mlx/build && make -C ./mlx/build -j4; \
		echo "$(GREEN)[mlx --> OK]$(CLEAR)"; \
    fi

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(OBJ_FILES)
	@echo "\n$(BLUE)Compiling libft.$(CLEAR)"
	@make -sC libft
	@echo "$(GREEN)[libft --> OK]$(CLEAR)"
	@echo "$(BLUE)Compiling cub3D program.$(CLEAR)"
	$(CC) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)[cub3D --> OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)"

clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	@make clean -sC libft
	$(RM) $(OBJ_DIR)
	$(RM) $(MLX_BUILD)
	@echo "$(GREEN)Object files removed correctly$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing binary files.$(CLEAR)"
	@make fclean -sC libft
	$(RM) $(NAME)
	@echo "$(GREEN)Object files and binary removed correctly$(CLEAR)"

re: fclean all

.PHONY:	all clean fclean re
