##
## EPITECH PROJECT, 2018
## irc
## File description:
## Makefile
##

all: client server

client:
	make -C ./irc_client

server:
	make -C ./irc_server

clean:
	make -C ./irc_client clean
	make -C ./irc_server clean

fclean:
	make -C ./irc_client fclean
	make -C ./irc_server fclean

re: fclean all

tests_run:
	make -C ./irc_server tests_run
	make -C ./irc_client tests_run

.PHONY: all client server clean fclean
