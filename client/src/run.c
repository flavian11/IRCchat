/*
** EPITECH PROJECT, 2018
** irc
** File description:
** run
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>

#include <netdb.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "proto.h"

static void	client_irc(int fd)
{
	char	buff[1024] = {0};
	int	r = 0;

	while (1) {
		while ((r = read(fd, buff, 1024)) > 0) {
			buff[r] = '\0';
			printf("%s", buff);
		}
		while ((r = read(0, buff, 1024)) > 0) {
			buff[r] = '\0';
			dprintf(fd, "%s", buff);
		}
	}
}

void	run_client(char *ip, int port)
{
	struct protoent		*pe = getprotobyname("TCP");
	struct sockaddr_in	s_in;
	int			fd;

	if (!pe)
		die("getprotobyname: %s", strerror(errno));
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		die("socket: %s", strerror(errno));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	inet_aton(ip, &s_in.sin_addr);
	if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(fd);
		die("connect: %s", strerror(errno));
	}
	client_irc(fd);
	close(fd);
}
