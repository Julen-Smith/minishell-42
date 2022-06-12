/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:47:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/12 15:44:50 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exec_echo(t_command *command, int start)
{
	int	x;

	if (command->command[start])
	{
		while (command->command[++start])
		{
			x = -1;
			while (command->command[start][++x])
				write(1, &command->command[start][x], 1);
			if (command->command[start + 1])
				write(1, " ", 1);
		}
	}
	exit_status = 0;
}

void	ft_echo(t_command *command)
{
	int	i;

	i = 1;
	if (command->command[1] && !ft_strncmp(command->command[1], "-n", 2))
	{
		while (command->command[1][++i])
		{
			if (command->command[1][i] != 'n')
			{
				ft_exec_echo(command, 0);
				write(1, "\n", 1);
				return ;
			}
		}
		ft_exec_echo(command, 1);
		return ;
	}
	ft_exec_echo(command, 0);
	write(1, "\n", 1);
}
