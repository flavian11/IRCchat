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
				dprintf(fd, "436 ERR_NICKCOLLISION\r\n");
				return ;
			}
		}
	}
	if (!e->nickname[fd])
		printf("welcome to %s !\n", opts);
	else
		printf("%s change his nickname into %s\n", e->nickname[fd], opts);
	e->nickname[fd] = opts;
}

static int check_error_join(t_env *e, const int fd, char *opts)
{
	int	i_chan = -1;

	if (strcmp(opts, "") == 0) {
		dprintf(fd, "461 JOIN: \"Not enough parameters\"\r\n");
		return 1;
	}
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL && strcmp(e->channel.chan_name[i], opts) == 0) {
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

void	join_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL && strcmp(e->channel.chan_name[i], opts) == 0)
			i_chan = i;
	while (e->channel.users[i_chan][i_name] != NULL)
		i_name++;
	e->channel.users[i_chan][i_name] = e->nickname[fd];
	dprintf(fd, "332 %s: ?\r\n", opts);
	dprintf(fd, "352 %s:", opts);
	for (int y = 0; y < MAX_USERS; y++)
		if (e->channel.users[i_chan][y] != NULL)
			dprintf(fd, " @+%s", e->channel.users[i_chan][y]);
	dprintf(fd, "\r\n366 %s:End of NAMES list\r\n", opts);
}

void	part_cmd(const char *line, t_env *e, const int fd)
{
	char	*opts = get_opts(line);
	int	i_chan = -1;
	int	i_name = 0;

	if (check_error_join(e, fd, opts) != 0)
		return;
	for (int i = 0; i < MAX_CHAN; i++)
		if (e->channel.chan_name[i] != NULL && strcmp(e->channel.chan_name[i], opts) == 0)
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

	while (i_chan < MAX_CHAN && strcmp(opts, e->channel.chan_name[i_chan]) != 0)
		i_chan++;
	if (i_chan >= MAX_CHAN)
		return ;
	dprintf(fd, "353 RPL_NAMREPLY %s:", e->channel.chan_name[i_chan]);
	for (int i = 0; i < MAX_USERS; i++)
		if (e->channel.users[i_chan][i] != NULL)
			dprintf(fd, " @+%s", e->channel.users[i_chan][i]);
	dprintf(fd, "\r\n366 RPL_ENDOFNAMES\r\n");
}
