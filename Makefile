NAME = cub

SRC = main.c
 
CC = cc

OBJ = $(SRC:.c=.o)

all : $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all~