/*
** EPITECH PROJECT, 2018
** irc
** File description:
** main
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "proto.h"

void	client_read(t_env *e, int fd)
{
	int	r;
	char	buff[4096];

	r = read(fd, buff, 4096);
	if (r > 0) {
		buff[r] = '\0';
		for (int i = 0; i < MAX_FD; i++)
			if (e->fd_type[i] == FD_CLIENT)
				dprintf(i, "%s: %s\n", e->nickname[i], buff);
	}
	else {
		printf("%d: Connection closed\n", fd);
		close(fd);
		e->fd_type[fd] = FD_FREE;
	}	
}

void	add_client(t_env *e, int s)
{
	int			cs;
	struct sockaddr_in	client_sin;
	socklen_t		client_sin_len = sizeof(client_sin);

	cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
	e->fd_type[cs] = FD_CLIENT;
	e->fct_read[cs] = client_read;
	e->fct_write[cs] = NULL;
}

void	server_read(t_env *e, int fd)
{
	printf("New client\n");
	add_client(e, fd);
}

void	add_server(t_env *e)
{
	int			s;
	struct sockaddr_in	sin;

	s = socket(PF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		exit(84);
	if (listen(s, 42) == -1)
		exit(84);
	e->fd_type[s] = FD_SERVER;
	e->fct_read[s] = server_read;
	e->fct_write[s] = NULL;
}

int	main(int ac, char **av)
{
	if (ac != 2 || strcmp(av[1], "--help") == 0)
		die(USAGE, av[0]);
	run_server(atoi(av[1]));
	return 0;
}
