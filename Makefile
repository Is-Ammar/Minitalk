
CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCC = client.c utils.c
SRCCB = client_bonus.c utils_bonus.c

SRCS = server.c utils.c
SRCSB = server_bonus.c utils_bonus.c

CLIENT = client
CLIENTB = client_bonus
SERVER = server
SERVERB = server_bonus

.PHONY: all bonus clean

all: $(CLIENT) $(SERVER)

bonus: $(CLIENTB) $(SERVERB)

$(CLIENT): 
	$(CC) $(CFLAGS) -o $(CLIENT) $(SRCC)

$(SERVER): 
	$(CC) $(CFLAGS) -o $(SERVER) $(SRCS)

$(CLIENTB): 
	$(CC) $(CFLAGS) -o $(CLIENTB) $(SRCCB)

$(SERVERB): 
	$(CC) $(CFLAGS) -o $(SERVERB) $(SRCSB)

clean:
	@rm -f $(CLIENT) $(SERVER)

fclean: clean
	@rm -f $(CLIENTB) $(SERVERB)

re: fclean all
