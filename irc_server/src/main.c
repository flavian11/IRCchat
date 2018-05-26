/*
** EPITECH PROJECT, 2018
** irc
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>

#include "proto.h"

int	main(int ac, char **av)
{
	if (ac != 2 || strcmp(av[1], "--help") == 0)
		die(USAGE, av[0]);
	run_server(atoi(av[1]), 0);
	return 0;
}
