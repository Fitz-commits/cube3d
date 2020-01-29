LIBFT_ROOT = ./libft
LIB_GRAPH = -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx

CC = gcc
CCFLAGS = -Wall -Werror -Wextra
INCLAGS = -I$(LIBFT_ROOT) $(LIB_GRAPH) 
RM = rm -f
LIB = ar rcs

NAME = Cube3D

SRC = math.c 	parsing.c	process_map.c	texHandling.c \
		free_ft.c main.c	bmp.c

OBJ = $(SRC:.c=.o)
	INCLUDE = cube3d.h mlx.h

all : libft_all $(NAME)

$(NAME) : $(OBJ)
	cp $(LIBFT_ROOT)/libft.a .
		$(CC) $(LIB_GRAPH) $(LIBFT_ROOT)/libft.a $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDE)
		$(CC) $(CCFLAGS) $(INCFLAGS) -c -o $@ $<
libft_all:
		$(MAKE) -C $(LIBFT_ROOT) all
libft_clean:
		$(MAKE) -C $(LIBFT_ROOT) clean
libft_fclean:
		$(MAKE) -C $(LIBFT_ROOT) fclean
clean: libft_clean
		$(RM) $(OBJ)

fclean: libft_fclean clean
		$(RM) $(NAME)

re: fclean all