/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** handle commands
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct.h"
#include "proto.h"
#include "macro.h"

void	quit_cmd(__attribute__((unused)) const char *line,
		t_env *e,
		const int fd)
{
	e->fd_type[fd] = FD_FREE;
	free(e->nickname[fd]);
	e->nickname[fd] = NULL;
	close(fd);
	for (int x = 0; x < MAX_FD; x++) {
		if (e->fd_type[x] == FD_CLIENT)
			dprintf(x, "%s", line);
	}
}

void	nick_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);

	for (int i = 0; i < MAX_FD; i++) {
		if (e->nickname[i]) {
			if (strcmp(e->nickname[i], opts) == 0) {
				dprintf(fd, "436 ERR_NICKCOLLISION\r\n");
				return ;
			}
		}
	}
	for (int x = 0; x < MAX_FD; x++) {
		if (e->fd_type[x] == FD_CLIENT)
			dprintf(x, "%s", line);
	}
	if (!e->nickname[fd])
		printf("welcome to %s !\n", opts);
	else
		printf("%s change his nickname into %s\n",
		e->nickname[fd], opts);
	e->nickname[fd] = opts;
}

void	list_cmd(const char *line, __attribute__((unused)) t_env *e, const int fd)
{
	char	*opts = get_opts(line);

	if (strcmp(opts, "") == 0) {
		dprintf(fd, "321 RPL_LISTSTART\r\n");
		for (int i = 0; i < MAX_CHAN; i++)
			dprintf(fd, "322 RPL_LIST %s\r\n", str_tab[i]);
		dprintf(fd, "323 RPL_LISTEND\r\n");
	}
}

void	users_cmd(__attribute__((unused)) const char *line, t_env *e, const int fd)
{
	char	check = 0;

	dprintf(fd, "392 RPL_USERSSTART\r\n");
	for (int i = 0; i < MAX_FD; i++)
		if (e->nickname[i] != NULL) {
			dprintf(fd, "393 RPL_USERS %s\r\n", e->nickname[i]);
			check++;
		}
	if (check == 0)
		dprintf(fd, "395 RPL_NOUSERS\r\n");
	dprintf(fd, "394 RPL_ENDOFUSERS\r\n");
}

void	names_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = 0;

	while (i_chan < MAX_CHAN
	&& strcmp(opts, e->channel.chan_name[i_chan]) != 0)
		i_chan++;
	if (i_chan >= MAX_CHAN)
		return ;
	dprintf(fd, "353 RPL_NAMREPLY %s:", e->channel.chan_name[i_chan]);
	for (int i = 0; i < MAX_USERS; i++)
		if (e->channel.users[i_chan][i] != NULL)
			dprintf(fd, " @+%s", e->channel.users[i_chan][i]);
	dprintf(fd, "\r\n366 RPL_ENDOFNAMES\r\n");
}
