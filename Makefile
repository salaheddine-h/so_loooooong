NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -Lminilibx-linux -lmlx -lXext -lX11 -lm  -g -fsanitize=address

SRC = get_len/get_next_line.c get_len/get_next_line_utils.c map_parsing.c helper.c so_long.c

MLX_PATH = ./minilibx-linux/



# MLX_FLAGS = -L$(~/minilibx) -lmlx -lXext -lX11 -lm -lz
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm


all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all



#-----------------------------------------------------------------#


# CC = cc

# CFLAGS = -Wall -Wextra -Werror 	#   #-g -fsanitize=address

# CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux

# SRC = get_len/get_next_line.c get_len/get_next_line_utils.c map_parsing.c helper.c so_long.c

# NAME = so_long

# # all : $(NAME)

# # %.o: %.c
# # 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# $(NAME) : $(SRC)
# 	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
# #  MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# # $(NAME): $(OBJS)
# # 	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)


# clean :
# 	rm -f $(NAME)

# flcean : clean
# 	rm -r $(NAME)

# re : fclean all

