/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:55:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/07 19:33:07 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//Revision
void	ft_exit(t_command *command)
{
	int i;
	
	write(1, "exit\n", 5);
	i = 0;
	while (command->command[i])
		i++;
	if (i > 2)
	{
		printf("Minishell : Too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (command->command[1])
	{
		i = 0;
		while (command->command[1][i])
		{
			if (ft_isalpha(command->command[1][i]))
			{
				printf("Minishell : %s %s\n",command->command[1] ,E_TARG);
				g_exit_status = 1;
				exit(0);		
			}
			i++;
		}
		exit(ft_atoi(command->command[1]));
		g_exit_status = ft_atoi(command->command[1]);
	}
	exit(0);
	g_exit_status = 0;
}
