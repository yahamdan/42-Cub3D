NAME = cub
LIBFT = libft/libft.a

SRC = main.c parsing/get_map.c parsing/get_next_line_utils.c parsing/get_next_line.c \
	ft_lstadd_back.c ft_lstlast.c ft_lstnew.c
 
CC = cc

OBJ = $(SRC:.c=.o)

all : $(NAME)


$(NAME) : $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(OBJ)  $(LIBFT)  -o $(NAME)

clean :
	rm -rf libft/*.o
	rm -rf $(OBJ)

fclean : clean
	rm -rf libft/*.a
	rm -rf $(NAME)

re : fclean all