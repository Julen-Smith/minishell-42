/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:55:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/09 20:50:06 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_command *command)
{
	write(1, "exit\n", 5);
	if (command->command[1])
	{
		exit(ft_atoi(command->command[1]));
		exit_status = ft_atoi(command->command[1]);
	}
	exit(0);
	exit_status = 0;
}
