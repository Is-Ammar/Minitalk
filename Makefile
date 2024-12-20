# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:51:43 by iammar            #+#    #+#              #
#    Updated: 2024/12/15 14:54:00 by iammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCC=client.c utils.c
SRCS=server.c utils.c

OBJC = $(SRCC:.c=.o)
OBJCB = $(SRCCB:.c=.o)

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

all:$(SERVER) $(CLIENT)

$(SERVER): $(SRCS)
			$(CC) $(CFLAGS) $(SRCS) -o server

$(CLIENT): $(SRCC)
			$(CC) $(CFLAGS) $(SRCC) -o client


clean: 
		rm -rf $(OBJC) $(OBJS)
		rm -rf $(OBJCB) $(OBJSB) 

fclean: clean
		rm -rf $(SERVER) $(CLIENT)
		rm -rf $(SERVER_BONUS) $(CLIENT_BONUS)

re :fclean all
