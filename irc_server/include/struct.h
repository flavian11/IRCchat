/*
** EPITECH PROJECT, 2018
** irc
** File description:
** struct
*/

#pragma once

#include "macro.h"

typedef void(*fct)();

typedef struct s_env
{
	char	fd_type[MAX_FD];
	fct	fct_read[MAX_FD];
	fct	fct_write[MAX_FD];
	int	port;
	char	*nickname[MAX_FD];
}		t_env;
