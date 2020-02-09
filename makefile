LIBFT_ROOT = ./libft
LIBFT = libft.a
LIB_GRAPH = -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx

CC = gcc
CCFLAGS = -Wall -Werror -Wextra
INCLAGS = -I$(LIBFT_ROOT) $(LIB_GRAPH) 
RM = rm -f
LIB = ar rcs

NAME = Cube3D

SRC = bmp.c		dda.c	draw.c	free_ft_bis.c	free_ft.c	ft_error.c \
	key_handling.c	key_up.c	math.c	parsing.c	process_map.c	\
	sprite_init.c	sprite_sort.c	tex_handling.c	utils.c main.c

OBJ = $(SRC:.c=.o)
	INCLUDE = cube3d.h mlx.h

all : libft_all $(NAME)

$(NAME) : $(OBJ)
	cp $(LIBFT_ROOT)/$(LIBFT) .
		$(CC) $(CCFLAGS) $(LIB_GRAPH) $(LIBFT_ROOT)/libft.a $(OBJ) -o $(NAME)

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
		$(RM) $(NAME) $(LIBFT)

re: fclean all
