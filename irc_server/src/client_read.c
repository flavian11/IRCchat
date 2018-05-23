/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** client read
*/

#include <stdbool.h>

#include <stdio.h>
#include <string.h>

#include "proto.h"
#include "macro.h"
#include "struct.h"

t_op	op_tab[] = {
	{"QUIT", &quit_cmd},
	{"NICK", &nick_cmd},
	{"JOIN", &join_cmd},
	{"PART", &part_cmd},
	{"LIST", &list_cmd},
	{"USERS", &users_cmd},
	{"NAMES", &names_cmd},
	{0, 0}
};

static bool	is_on_chan(const char *nick, const char *nick2, t_env *e)
{
	int	check = 0;

	for (int i = 0; i < MAX_CHAN; i++) {
		for (int y = 0; y < MAX_USERS; y++) {
			if (e->channel.users[i][y] != NULL
			&& (strcmp(e->channel.users[i][y], nick) == 0
			|| strcmp(e->channel.users[i][y], nick2) == 0))
				check++;
		}
		if (check == 2)
			return true;
		check = 0;
	}
	return false;
}

static void	send_message(t_env *e, const char *line)
{
	char	*nick = get_nick(line);

	for (int i = 0; i < MAX_FD; i++) {
		if (e->fd_type[i] == FD_CLIENT && strcmp(e->nickname[i], nick) != 0
		    && is_on_chan(nick, e->nickname[i], e))
			dprintf(i, "%s", line);
	}
}

static void	parse_line(const char *line, t_env *e, const int fd)
{
	char	*cmd = get_cmd(line);
	int	i = 0;

	while(op_tab[i].cmd != NULL && strcmp(op_tab[i].cmd, cmd) != 0)
		i++;
	if (op_tab[i].cmd != NULL)
		op_tab[i].fcn(line, e, fd);
	else
		send_message(e, line);
}

void	client_read(t_env *e, int fd)
{
	char	*line = NULL;
	size_t	len = 0;
	FILE	*stream = fdopen(fd, "rw");

	getline(&line, &len, stream);
	printf("line: '%s'\n", line);
	parse_line(line, e, fd);
}
