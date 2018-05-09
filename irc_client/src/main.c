/*
** EPITECH PROJECT, 2018
** irc
** File description:
** main
*/

#include <stdlib.h>

#include "proto.h"
#include "macro.h"

int	main(int ac, char **av)
{
	if (ac != 3)
		die(USAGE, av[0]);
	run_client(av[1], atoi(av[2]));
	return 0;
}
