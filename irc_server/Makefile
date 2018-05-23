##
## EPITECH PROJECT, 2018
## irc
## File description:
## Makefile
##

ECHO            =       /bin/echo -e
DEFAULT =       "\033[00m"
GREEN           =       "\033[0;32m"
TEAL            =       "\033[1;36m"
RED                     =       "\033[0;31m"

CC      =       gcc

RM      =       rm -f

SRC     =       ./src/

SRCS    =       $(SRC)main.c \
		$(SRC)run.c \
		$(SRC)die.c \
		$(SRC)client_read.c \
		$(SRC)op.c \
		$(SRC)string_handling.c

OBJ     =       $(SRCS:.c=.o)

NAME    =       ../server

CFLAGS  +=      -I ./include -W -Wextra -Wall -g

all:    $(NAME)

$(NAME):        $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(SRCS:.c=.c~)
	@$(RM) $(SRCS:.c=.c#)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.c.o:
	@gcc $(CFLAGS) -c $< -o $@ && \
                 $(ECHO) $(GREEN) "[ OK ]" $(TEAL) $< $(DEFAULT) || \
                 $(ECHO) $(RED) "[ XX ]" $(TEAL) $< $(DEFAULT)

