/*
** EPITECH PROJECT, 2018
** irc
** File description:
** struct
*/

#pragma once

#include "macro.h"

typedef void(*fct)();

typedef struct s_chan
{
	char	*chan_name[MAX_CHAN];
	char	*users[MAX_CHAN][MAX_USERS];
}		t_chan;

typedef struct s_env
{
	char	fd_type[MAX_FD];
	fct	fct_read[MAX_FD];
	fct	fct_write[MAX_FD];
	int	port;
	char	*nickname[MAX_FD];
	t_chan	channel;
}		t_env;

typedef struct s_op
{
	char	*cmd;
	void	(*fcn)(const char *, t_env *, const int);
}		t_op;

char	*str_tab[MAX_CHAN];
