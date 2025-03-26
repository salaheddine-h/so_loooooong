NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -Lminilibx-linux -lmlx -lXext -lX11 -lm  #-g -fsanitize=address

SRC = get_len/get_next_line.c get_len/get_next_line_utils.c map_parsing.c helper.c so_long.c

MLX_PATH = ./minilibx-linux/


MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
