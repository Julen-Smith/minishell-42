/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:40:06 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 13:47:00 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool char_is_redir(char command_i)
{
	if(command_i == '<' || command_i == '>')
		return (true);
	return (false);
}

void ft_fill_positions_to_command(t_command *command, int *position_stack)
{
	int i;

	i = 0;
	command->redirpos = malloc (sizeof(int) * command->redircnt);
	printf("Recuento de reddir : %d\n",command->redircnt);
	while(i != command->redircnt)
	{
		command->redirpos[i] = position_stack[i];
		printf("Las posiciones estan en %d\n",command->redirpos[i]);
		i++;
	}
}

bool count_check_redirs(t_command *command)
{
	int i;
	int poslvl;
	int positions[200];
	
	i = 0;
	poslvl = 0;
	while(command->command[i])
	{
		if (command->command[i][0] != 39 && command->command[i][0] != 34)
			if (char_is_redir(command->command[i][0]))
			{
				positions[poslvl] = i;
				poslvl++;	
			}
		i++;
	}
	command->redircnt = poslvl;
	printf("Las posiciones estan en %d\n",command->redircnt);
	ft_fill_positions_to_command(command, positions);
	return (true);
}

bool contains_redir(t_command *command)
{
	if (_contains(command->command,HDC))
		return (1);
	if (_contains(command->command,APD))
		return (2);
	if (_contains(command->command,REDIPT))
		return (3);
	if	(_contains(command->command,REDOPT))
		return (4);
	return (0);
}

bool	manage_redir_symbols(t_command *command)
{
	if (contains_redir(command))
	{
		if (count_check_redirs(command))
			return (false);
		fprintf(stderr,"Manage reddir symbols");
		return (true);	
	}
	return (false);
}