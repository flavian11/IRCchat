/*
** EPITECH PROJECT, 2018
** irc
** File description:
** test
*/

#include <criterion/criterion.h>

#include <string.h>

#include "proto.h"

Test(utils, get_cmd_test)
{
	char	*cmd_line = strdup("USER anonymous");
	char	*cmd;

	if (!cmd_line)
		exit(84);
	cmd = get_cmd(cmd_line);
	if (!cmd)
		exit(84);
	cr_assert(strcmp(cmd, "USER") == 0);
}
