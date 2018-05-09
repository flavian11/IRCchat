##
## EPITECH PROJECT, 2018
## irc
## File description:
## Makefile
##

all: client server

client:
	make -C ./client

server:
	make -C ./server

clean:
	make -C ./client clean
	make -C ./server clean

fclean:
	make -C ./client fclean
	make -C ./server fclean

re: fclean all

.PHONY: all client server clean fclean
