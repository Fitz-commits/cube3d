# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 15:39:16 by cdelaby           #+#    #+#              #
#    Updated: 2020/02/15 15:39:46 by cdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Werror -Wextra

NAME = libft.a

SRC = ft_atoi.c       ft_isdigit.c    ft_memmove.c    ft_split.c \
		ft_strlcpy.c    ft_strnstr.c  ft_bzero.c      ft_isprint.c \
		ft_memset.c     ft_strchr.c     ft_strlen.c     ft_strrchr.c \
		ft_calloc.c      ft_putchar_fd.c ft_strcpy.c     ft_strmapi.c \
		ft_strstr.c 	ft_isalnum.c    ft_memchr.c     ft_putendl_fd.c \
		ft_strdup.c     ft_strncmp.c    ft_strtrim.c 	ft_isalpha.c \
		ft_memcmp.c     ft_putnbr_fd.c  ft_strjoin.c    ft_strncpy.c \
		ft_substr.c 	ft_isascii.c    ft_memcpy.c     ft_putstr_fd.c \
		ft_strlcat.c    ft_strndup.c    ft_tolower.c 	ft_toupper.c \
		ft_memccpy.c	ft_strcat.c 	ft_strncat.c	ft_strcmp.c	\
		ft_calloc.c		ft_get_size.c	ft_gnl.c	ft_stradd.c
SRC_1 = ft_lstadd_back_bonus.c	ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
		ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c 
OBJ_1 = $(SRC_1:.c=.o)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft.h
	ar rc $(NAME) $(OBJ)

bonus : $(OBJ_1)
	ar rc libft.a $(OBJ_1)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) ${OBJ_1}

fclean: clean
	rm -f $(NAME)

re: fclean all
