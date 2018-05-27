/*
** EPITECH PROJECT, 2018
** irc
** File description:
** proto
*/

#pragma once

#include "struct.h"

void	run_server(int, int);
void	die(const char *, ...);
void	add_server(t_env *);
void	client_read(t_env *, int);

/* cmd handling */
void	quit_cmd(__attribute__((unused)) const char *, __attribute__((unused)) t_env *, const int);
void	nick_cmd(const char *, t_env *, const int);
void	join_cmd(const char *, t_env *, const int);
void	part_cmd(const char *, t_env *, const int);
void	list_cmd(const char *, t_env *, const int);
void	users_cmd(const char *, t_env *, const int);
void	names_cmd(const char *, t_env *, const int);
void	priv_cmd(const char *, t_env *, const int);

/* string handling */
char    *get_cmd(const char *);
char    *get_opts(const char *);
char	*get_nick(const char *);