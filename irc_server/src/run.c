/*
** EPITECH PROJECT, 2018
** irc
** File description:
** run server
*/

#include <sys/time.h>
#include <sys/types.h>

#include <unistd.h>

#include "struct.h"
#include "macro.h"

void	run_server(int port)
{
	t_env		e = {{FD_FREE}, {NULL}, {NULL}, port, {NULL}};
	int		fd_max;
	fd_set		fd_read;
	struct timeval	tv = {20, 0};

	e.port = port;
	add_server(&e);
	while (1) {
		FD_ZERO(&fd_read);
		fd_max = 0;
		for (int i = 0; i < MAX_FD; i++)
			if (e.fd_type[i] != FD_FREE) {
				FD_SET(i, &fd_read);
				fd_max = i;
			}
		if (select(fd_max + 1, &fd_read, NULL, NULL, &tv) == -1)
			perror("select");
		for (int j = 0; j < MAX_FD; j++)
			if (FD_ISSET(j, &fd_read))
				e.fct_read[j](&e, j);
	}
}
