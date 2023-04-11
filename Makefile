NAME		= server
NAMI		= client
FLAGS	= -Wall -Wextra -Werror

all: ${NAME} ${NAMI}

${NAME}: server.c
	@cc ${FLAGS} server.c -o server

${NAMI}: client.c
	@cc ${FLAGS} client.c -o client

clean:
	@rm -f server 
	@rm -f client
fclean: clean

re: fclean all
