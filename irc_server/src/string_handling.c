/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** string handling
*/

#include <errno.h>

#include <string.h>

#include "proto.h"

static size_t   custom_strlen(const char *str, const char c)
{
	size_t  i = 0;

	while (str[i] != '\0' && str[i] != c
	&& str[i] != '\n' && str[i] != '\r')
		i++;
	return i;
}

static char	*get_custom_cmd(const char *cmd_line)
{
	int	x = 0;

	for (int i = 0; cmd_line[i] != ' ' && cmd_line[i] != '\0'; i++)
		x = i;
	x += 2;
	return get_cmd(&cmd_line[x]);
}

char    *get_cmd(const char *cmd_line)
{
	size_t  i = custom_strlen(cmd_line, ' ');
	char    *res = NULL;

	if (cmd_line[0] == ':')
		res = get_custom_cmd(cmd_line);
	else
		res = strndup(cmd_line, i);
	if (!res)
		die("malloc error: %s", strerror(errno));
	return res;
}

char    *get_opts(const char *cmd_line)
{
	size_t  i = custom_strlen(cmd_line, ' ');
	char    *res = strdup(&cmd_line[i + 1]);
	int	y;

	if (cmd_line[0] == ':') {
		for (int x = 0; cmd_line[x] != ' ' && cmd_line[x] != '\0'; x++)
			y = x;
		y += 2;
		return get_opts(&cmd_line[y]);
	}
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

char	*get_nick(const char *line)
{
	size_t	i = custom_strlen(line, ':');
	char	*res = strndup(line, i);

	if (!res)
		die("malloc error: %s", strerror(errno));
	return res;
}
