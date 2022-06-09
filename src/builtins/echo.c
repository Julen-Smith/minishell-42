/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:47:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/08 21:57:08 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exec_echo(t_command *command, int start, int flag)
{
	int	x;

	while (command->command[++start])
	{
		x = -1;
		while (command->command[start][++x])
			write(1, &command->command[start][x], 1);
		if (command->command[start + 1])
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
}

void	ft_echo(t_command *command)
{
	int	i;

	i = 1;
	if (!ft_strncmp(command->command[1], "-n", 2))
	{
		while (command->command[1][++i])
		{
			if (command->command[1][i] != 'n')
			{
				ft_exec_echo(command, 0, 1);
				return ;
			}
		}
	}
	ft_exec_echo(command, 1, 0);
}
