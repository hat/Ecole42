# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thendric <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/11 16:31:24 by thendric          #+#    #+#              #
#    Updated: 2017/02/13 20:37:44 by thendric         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=fdf

CC			=gcc

INC			=-I$(INCDIR)

CFLAGS		=-Wall -Wextra -Werror
GFLAGS		=-framework OpenGL -framework AppKit

FILES		=main.c draw.c map.c managers.c circle.c

BUILDIR		=build
SRCDIR		=sources

SRCS		=$(addprefix $(SRCDIR)/, $(FILES))
OBJECTS		=$(FILES:.c=.o)

INCDIR		=includes/
LIBS		=libft/libft.a minilibx_macos/libmlx.a

.PHONY: all clean fclean re

all: $(NAME)

$(LIB)/$(LIB).a:
	$(MAKE) -C $(LIB)

$(NAME):
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(CFLAGS) $(GFLAGS) -o $(NAME) $(INC) $(FILES) $(LIBS)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME) $(OBJECTS)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

42: re
	./$(NAME) ~/Documents/fdf_stuff/test_maps/42.fdf

mars: re
	./$(NAME) ~/Documents/fdf_stuff/test_maps/mars.fdf

re: fclean all
