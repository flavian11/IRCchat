/*
** EPITECH PROJECT, 2018
** irc
** File description:
** tests
*/

#include <criterion/criterion.h>

#include <string.h>

#include "proto.h"

Test(utils, get_nick_test)
{
	char	*cmd_line = strdup("lolilol: NICK mdr");
	char	*nick;

	if (!cmd_line)
		exit(84);
	nick = get_nick(cmd_line);
	cr_assert(strcmp(nick, "lolilol") == 0);
}
