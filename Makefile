# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abchan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/08 16:09:04 by abchan            #+#    #+#              #
#    Updated: 2018/06/22 15:39:34 by abchan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FILES = main.c \
        readnparse.c \
		keyninit.c \
		draw.c \
		projection.c \
		matrix.c \
		transformation.c \
		transformation2.c
		

OBJ = $(FILES:.c=.o)

HEADER = -I./

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT_LIB = ./$(LIBFT_PATH)libft.a
LIBFT_LINK = -L$(LIBFT_PATH) -lft

MLX_PATH = ./minilibx_macos/
MLX_LIB = ./$(MLX_PATH)libmlx.a
MLX_LINK = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(OBJ) $(MLX_LINK) $(LIBFT_LINK) -o $(NAME)

$(OBJ):
	$(CC) $(CFLAGS) -c $(FILES) $(HEADER)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH) re

$(MLX_LIB):
	make -C $(MLX_PATH) re

debug: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(FILES) $(HEADER) $(MLX_LINK) $(LIBFT_LINK) -g -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH) re

$(MLX_LIB):
	make -C $(MLX_PATH) re

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
