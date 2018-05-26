/*
** EPITECH PROJECT, 2018
** irc
** File description:
** string handling
*/

#include <errno.h>

#include <stdlib.h>
#include <string.h>

#include "proto.h"

static size_t   custom_strlen(const char *str)
{
	size_t  i = 0;

	while (str[i] != '\0' && str[i] != ' '
	&& str[i] != '\n' && str[i] != '\r')
		i++;
	return i;
}

char    *get_cmd(const char *cmd_line)
{
	size_t  i = custom_strlen(cmd_line);
	char    *res = strndup(cmd_line, i);

	if (!res)
		die("malloc error: %s", strerror(errno));
	return res;
}

char    *get_opts(const char *cmd_line)
{
	size_t  i = custom_strlen(cmd_line);
	char    *res = strdup(&cmd_line[i + 1]);

	if (!res)
		die("malloc error: %s", strerror(errno));
	i = 0;
	while (res[i]) {
		if (res[i] == '\r' || res[i] == '\n')
			res[i] = '\0';
		i++;
	}
	return res;
}
