/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** client read
*/

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
	{0, 0}
};

static void	send_message(t_env *e, const char *line)
{
	for (int i = 0; i < MAX_FD; i++) {
		if (e->fd_type[i] == FD_CLIENT)
			dprintf(i, "%s: %s\n", e->nickname[i], line);
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
