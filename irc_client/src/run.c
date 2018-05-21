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
#include "struct.h"

op_t	op_tab[] = {
	{"/nick", &nick_handling},
	{"/list", &list_handling},
	{"/quit", &quit_handling},
	{"/join", &join_handling},
	{"/part", &part_handling},
	{0, 0}
};

static void	parse_line(const char *line, const int fd)
{
	char	*cmd;

	if (line[0] == '/') {
		cmd = get_cmd(line);
		for (int i = 0; op_tab[i].cmd != NULL; i++) {
			if (strcmp(cmd, op_tab[i].cmd) == 0) {
				op_tab[i].fcn(fd, line);
				break ;
			}
		}
	}
	else
		dprintf(fd, "%s: %s\r\n", g_nickname, line);
}

static void	client_irc(int fd)
{
	FILE	*stream = fdopen(fd, "rw");
	char	*line = NULL;
	size_t	len = 0;
	fd_set	rfds;
	struct timeval	tv = {2, 0};

	while (1) {
		FD_SET(0, &rfds);
		FD_SET(fd, &rfds);
		if (select(fd + 1, &rfds, NULL, NULL, &tv) == -1)
			die("select: %s", strerror(errno));
		if (FD_ISSET(0, &rfds)) {
			getline(&line, &len, stdin);
			parse_line(line, fd);
		}
		if (FD_ISSET(fd, &rfds)) {
			getline(&line, &len, stream);
			printf("%s", line);
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
	dprintf(fd, "NICK %s\r\n", g_nickname);
	client_irc(fd);
	close(fd);
}
