/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** struct.h
*/

#pragma once

char	*g_nickname;

typedef struct s_op
{
	char	*cmd;
	void	(*fcn)(const int, const char *);
}	op_t;
