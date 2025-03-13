CC = cc 

CFLAGS = -Wall -Wextra -Werror 	#   #-g -fsanitize=address

SRC = get_len/get_next_line.c get_len/get_next_line_utils.c map_parsing.c helper.c so_long.c

NAME = so_long

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME)

flcean : clean
	rm -r $(NAME)

re : fclean all