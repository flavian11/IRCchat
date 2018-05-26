/*
** EPITECH PROJECT, 2018
** irc
** File description:
** channel handling cmd
*/

#include <string.h>
#include <stdio.h>

#include "struct.h"
#include "proto.h"

static int check_error_join(t_env *e, const int fd, char *opts)
{
	int	i_chan = -1;

	if (strcmp(opts, "") == 0) {
		dprintf(fd, "461 JOIN: \"Not enough parameters\"\r\n");
		return 1;
	}
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL
		&& strcmp(e->channel.chan_name[i], opts) == 0) {
			i_chan = i;
			break ;
		}
	if (i_chan == -1) {
		for (int y = 0; y < MAX_CHAN; y++)
			if (e->channel.chan_name[y] == NULL) {
				e->channel.chan_name[y] = strdup(opts);
				break ;
			}
	}
	return 0;
}

static void	send_cmd(t_env *e, const char *line)
{
	for (int y = 0; y < MAX_FD; y++) {
		if (e->fd_type[y] == FD_CLIENT)
			dprintf(y, "%s", line);
	}
}

void	join_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL
		&& strcmp(e->channel.chan_name[i], opts) == 0)
			i_chan = i;
	while (e->channel.users[i_chan][i_name] != NULL)
		i_name++;
	e->channel.users[i_chan][i_name] = e->nickname[fd];
	send_cmd(e, line);
	dprintf(fd, "332 %s: ?\r\n", opts);
	dprintf(fd, "353 %s:", opts);
	for (int y = 0; y < MAX_USERS; y++)
		if (e->channel.users[i_chan][y] != NULL)
			dprintf(fd, " @+%s", e->channel.users[i_chan][y]);
	dprintf(fd, "\r\n366 %s:End of NAMES list\r\n", opts);
}

static int	is_on_chan(t_env *e, int i_chan, int i_name, int fd)
{
	if (strcmp(e->channel.users[i_chan][i_name],
		e->nickname[fd]) != 0) {
		dprintf(fd,
			"442 You're not on that channel\r\n");
		return -1;
	}
	return 0;
}

void	part_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL
		&& strcmp(e->channel.chan_name[i], opts) == 0)
			i_chan = i;
	for (int x = 0;
	strcmp(e->channel.users[i_chan][x], e->nickname[fd]) != 0
		&& x < MAX_USERS; x++)
		i_name = x;
	if (i_name == MAX_USERS - 1)
		if (is_on_chan(e, i_chan, i_name, fd) == -1)
			return ;
	send_cmd(e, line);
	e->channel.users[i_chan][i_name] = NULL;
}
