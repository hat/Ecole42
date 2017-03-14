NAME	= hydra
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRV		= server
CLI		= client
S_EXEC	= server_exec
C_EXEC	= client_exec
SRCS	= server.c new_client.c
LDIR	= includes
OBJS	= $(SRCS:.c=.o)

.PHONY: all make fclean re server client

all: $(NAME)

$(NAME):
	make $(SRV)
	make $(CLI)

$(SRV):
	$(CC) $(CFLAGS) $(SRV).c -I$(LDIR) -o $(S_EXEC)

$(CLI):
	$(CC) $(CFLAGS) $(CLI).c -I$(LDIR) -o $(C_EXEC)

clean:
	rm -rf $(SRV).o
	rm -rf $(CLI).o

fclean: clean
	rm -rf $(S_EXEC)
	rm -rf $(C_EXEC)

re: fclean all