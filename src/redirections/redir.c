/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:40:06 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 12:54:54 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool char_is_redir(char *command_i)
{
	if(command_i[0] == '<' || command_i[0] == '>')
		return (true);
}

void ft_fill_positions_to_command(t_command *command, int *position_stack)
{
	int i;

	i = 0;
	command->redirorder = malloc (sizeof(int) * command->redircnt);
	while(i != command->redircnt)
	{
		command->redirorder[i] = position_stack[i];
		//printf("Las redirecciones estan en las posiciones %d\n", command->redirorder[i]);
		i++;
	}
}

bool count_check_redirs(t_command *command)
{
	int i;
	int u;
	int poslvl;
	int positions[200];
	
	i = 0;
	u = 0;
	poslvl = 0;
	while(command->command[i])
	{
		if (char_is_redir(command->command[i]))
		{
			u++;
			printf("Las redirecciones estan en las posiciones %d\n",i);
			positions[poslvl] = i;
			poslvl++;	
		}
		i++;
	}
	command->redircnt = u;
	ft_fill_positions_to_command(command,positions);
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