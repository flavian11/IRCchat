/*
** EPITECH PROJECT, 2018
** irc
** File description:
** proto
*/

#pragma once

void	die(const char *, ...);
void	run_client(char *, int);

/* string handling */
char	*get_cmd(const char *);
char    *get_opts(const char *);

/* cmd handling */
void	nick_handling(const int, const char *);
void	list_handling(const int, const char *);
void	quit_handling(const int, const char *);
void	join_handling(const int, const char *);
void	part_handling(const int, const char *);
void	users_handling(const int, const char *);
void	names_handling(const int, const char *);
void	msg_handling(const int, const char *);
