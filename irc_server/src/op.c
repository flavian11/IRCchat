/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** handle commands
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "struct.h"
#include "proto.h"
#include "macro.h"

void	quit_cmd(__attribute__((unused)) const char *line,
		__attribute__((unused)) t_env *e,
		const int fd)
{
	close(fd);
	e->fd_type[fd] = FD_FREE;
}

void	nick_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);

	for (int i = 0; i < MAX_FD; i++) {
		if (e->nickname[i]) {
			if (strcmp(e->nickname[i], opts) == 0) {
				dprintf(fd, "ERR_NICKCOLLISION\r\n");
				return ;
			}
		}
	}
	if (!e->nickname[fd])
		printf("welcome to %s !\n", opts);
	else
		printf("%s change his nickname into %s", e->nickname[fd], opts);
	e->nickname[fd] = opts;
}
