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
		__attribute__((unused)) t_env *e,
		const int fd)
{
	e->fd_type[fd] = FD_FREE;
	free(e->nickname[fd]);
	e->nickname[fd] = NULL;
	close(fd);
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

static int check_error_join(t_env *e, const int fd, const char *opts)
{
	int	i_chan = -1;

	if (strcmp(opts, "") == 0) {
		dprintf(fd, "461 JOIN: \"Not enough parameters\"\r\n");
		return 1;
	}
	for (int i = 0; i < MAX_CHAN; i++)
		if (strcmp(e->channel.chan_name[i], opts) == 0) {
			i_chan = i;
			break ;
		}
	if (i_chan == -1) {
		dprintf(fd, "403 %s: No such channel\r\n", opts);
		return 1;
	}
	return 0;
}

void	join_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (strcmp(e->channel.chan_name[i], opts) == 0)
			i_chan = i;
	for (int x = 0; e->channel.users[i_chan][x] != NULL; x++)
		i_name = x;
	e->channel.users[i_chan][i_name] = e->nickname[fd];
	dprintf(fd, "332 %s: ?\r\n", opts);
	dprintf(fd, "352 %s: ", opts);
	for (int y = 0; y < MAX_USERS; y++)
		if (e->channel.users[i_chan][y] != NULL)
			dprintf(fd, "@+%s", e->channel.users[i_chan][y]);
	dprintf(fd, "\r\n366 %s:End of NAMES list", opts);
}

void	part_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (strcmp(e->channel.chan_name[i], opts) == 0)
			i_chan = i;
	for (int x = 0; strcmp(e->channel.users[i_chan][x], e->nickname[fd]) != 0 && x < MAX_USERS; x++)
		i_name = x;
	if (i_name == MAX_USERS - 1)
		if (strcmp(e->channel.users[i_chan][i_name], e->nickname[fd]) != 0) {
			dprintf(fd, "442 %s:You're not on that channel\r\n", opts);
			return ;
		}
	e->channel.users[i_chan][i_name] = NULL;
}
