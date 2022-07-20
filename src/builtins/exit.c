/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:55:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/20 18:01:17 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exit_arg(t_command_table *table, int c_num, int count)
{
	int	i;

	i = 0;
	while (table->commands[c_num].command[1][i])
	{
		if (ft_isalpha(table->commands[c_num].command[1][i]))
		{
			printf("Minishell : %s %s\n", table->commands[c_num].command[1], E_TARG);
			g_exit_status = 1;
			if (count == 1)
			{
				ft_free_commands(table);
				exit(0);
			}
		}
		i++;
	}
	g_exit_status = ft_atoi(table->commands[c_num].command[1]);
	if (count == 1)
	{
		ft_free_commands(table);
		exit(ft_atoi(table->commands[c_num].command[1]));
	}
}

int	ft_exit(t_command_table *table, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (count == 1)
		write(1, "exit\n", 5);
	i = 0;
	while (table->commands[c_num].command[i])
		i++;
	if (i > 2)
	{
		printf("Minishell : Too many arguments\n");
		g_exit_status = 1;
		return (0);
	}
	if (table->commands[c_num].command[1])
		ft_exit_arg(table, c_num, count);
	g_exit_status = 0;
	if (count == 1)
	{
		ft_free_commands(table);
		exit(0);
	}
	return (0);
}
