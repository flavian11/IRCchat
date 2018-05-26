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

TEST	=	./tests/

SRCS    =       $(SRC)main.c \
		$(SRC)die.c \
		$(SRC)run.c \
		$(SRC)string_handling.c \
		$(SRC)op.c

TESTS	=	$(SRC)die.c \
		$(SRC)run.c \
		$(SRC)string_handling.c \
		$(SRC)op.c \
		$(TEST)tests-get_cmd.c

OBJ     =       $(SRCS:.c=.o)

OBJTEST	=	$(TESTS:.c=.o)

NAME    =       ../client

NAME_TEST	=	./criterion

CFLAGS  +=      -I ./include -W -Wextra -Wall

all:    $(NAME)

$(NAME):        $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(SRCS:.c=.c~)
	@$(RM) $(SRCS:.c=.c#)
	@$(RM) $(OBJTEST)
	@$(RM) $(TESTS:.c=.c~)
	@$(RM) $(TESTS:.c=.c#)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)

re: fclean all

tests_run:	$(OBJTEST)
	$(CC) $(OBJTEST) -o $(NAME_TEST) -lcriterion -coverage
	$(NAME_TEST) --verbose

.c.o:
	@gcc $(CFLAGS) -c $< -o $@ && \
                 $(ECHO) $(GREEN) "[ OK ]" $(TEAL) $< $(DEFAULT) || \
                 $(ECHO) $(RED) "[ XX ]" $(TEAL) $< $(DEFAULT)

