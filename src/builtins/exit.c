/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:55:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/15 09:46:14 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_command *command)
{
	write(1, "exit\n", 5);
	if (command->command[1])
	{
		exit(ft_atoi(command->command[1]));
		g_exit_status = ft_atoi(command->command[1]);
	}
	exit(0);
	g_exit_status = 0;
}
