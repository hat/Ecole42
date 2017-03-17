NAME	=
CC	=gcc
CFLAGS	=-Wall -Wextra -Werror
CFLAGS	+=-I$(IDIR)
IDIR	=inc

FILES	=
SDIR	=srcs
ODIR	=objs
SRC	=$(addprefix $(SDIR)/, $(FILES))
OBJ	=$(addprefix $(ODIR)/, $(FILES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

NAME: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)%.o: $(SDIR)%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
	mkdir $(ODIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)
