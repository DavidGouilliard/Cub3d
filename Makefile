SRC = main.c utils.c raycasting.c rendering.c game_loop.c player_move.c debug.c init.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I/usr/include -Imlx
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT = ./libft/libft.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g3
NAME = Cub3d

all: $(LIBFT) $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT):
	@make -C ./libft

clean:
	rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
