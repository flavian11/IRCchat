/*
** EPITECH PROJECT, 2018
** irc
** File description:
** proto
*/

#pragma once

#include "struct.h"

void	run_server(int);
void	die(const char *, ...);
void	add_server(t_env *);
void	client_read(t_env *, int);

/* cmd handling */
void	quit_cmd(__attribute__((unused)) const char *, __attribute__((unused)) t_env *, const int);
void	nick_cmd(const char *, t_env *, const int);

/* string handling */
char    *get_cmd(const char *);
char    *get_opts(const char *);
