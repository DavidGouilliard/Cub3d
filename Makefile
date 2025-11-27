SRC =	main.c \
	   	parser/parser.c \
		parser/error.c \
		parser/string_utils.c \
	   	parser/parse_header/parse_header_utils.c \
	   	parser/parse_header/parse_header_checks.c \
	   	parser/parse_header/parse_header.c \
	   	parser/parse_map/parse_map.c \
	   	parser/parse_map/validate_map.c \
		exec/utils.c \
		exec/raycasting.c \
		exec/rendering.c \
		exec/game_loop.c \
		exec/player_move.c \
		exec/debug.c \
		exec/init.c \

OBJ = $(SRC:.c=.o)
INCLUDES = -I/usr/include -Imlx
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT = ./libft/libft.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g3
NAME = cub3d

all: $(LIBFT) $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I. -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I. -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

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
