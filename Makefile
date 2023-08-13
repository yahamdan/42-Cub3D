NAME = cub
MLX = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz
LIBFT = libft/libft.a

SRC = main.c parsing/get_map.c parsing/get_next_line_utils.c parsing/get_next_line.c \
	ft_lstadd_back.c ft_lstlast.c ft_lstnew.c
 
CC = cc

OBJ = $(SRC:.c=.o)

all : $(NAME)


$(NAME) : $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(OBJ)  $(LIBFT)  $(MLX) -o $(NAME)

clean :
	rm -rf libft/*.o
	rm -rf $(OBJ)

fclean : clean
	rm -rf libft/*.a
	rm -rf $(NAME)

re : fclean all