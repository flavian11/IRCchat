/*
** EPITECH PROJECT, 2018
** irc
** File description:
** op handling
*/

#include <string.h>
#include <stdio.h>

#include "proto.h"
#include "struct.h"

void	nick_handling(const int fd, const char *line)
{
	char	*opts = get_opts(line);

	dprintf(fd, ":%s NICK %s\r\n", g_nickname, opts);
	g_nickname = opts;
}

void	list_handling(const int fd, const char *line)
{
	char	*opts = get_opts(line);

	if (strcmp(opts, "") == 0)
		dprintf(fd, "LIST\r\n");
	else
		dprintf(fd, "LIST %s\r\n", opts);
}

void	quit_handling(const int fd, __attribute__((unused)) const char *line)
{
	dprintf(fd, "QUIT\r\n");
}

void	join_handling(const int fd, const char *line)
{
	char	*opts = get_opts(line);

	dprintf(fd, "JOIN %s\r\n", opts);
}

void	part_handling(const int fd, const char *line)
{
	char	*opts = get_opts(line);

	dprintf(fd, "PART %s\r\n", opts);
}

void	users_handling(const int fd, __attribute__((unused)) const char *line)
{
	dprintf(fd, "USERS\r\n");
}

void	names_handling(const int fd, const char *line)
{
	char	*opts = get_opts(line);

	dprintf(fd, "NAMES %s\r\n", opts);
}
