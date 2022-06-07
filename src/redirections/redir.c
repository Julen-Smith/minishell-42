/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:40:06 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/07 11:42:28 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	char_is_redir(char command_i)
{
	if (command_i == '<' || command_i == '>')
		return (true);
	return (false);
}

void	ft_fill_positions_to_command(t_command *command, int *position_stack)
{
	int	i;

	i = 0;
	command->redirpos = malloc (sizeof(int) * command->redircnt);
	while(i != command->redircnt)
	{
		command->redirpos[i] = position_stack[i];
		i++;
	}
}

bool check_and_manage_order(t_command *command)
{
	int i;
	int u;

	i = 0;
	u = 0;
	command->redirorder = malloc (sizeof (char *) * (command->redircnt + 1));
	command->redirorder[command->redircnt] = NULL;
	while(i != command->redircnt)
	{
		command->redirorder[i] =  malloc (sizeof(char) * (2 + 1));
		command->redirorder[i][2] = '\0';
		i++;
	}
	i = 0;
	while(i != command->redircnt)
	{
		if(ft_strlen(command->command[command->redirpos[i]]) > 2)
			return (false);
		else
		{
			if(_str_contains(command->command[command->redirpos[i]],HDC))
				command->redirorder[i] = ft_strdup("<<");       
			else if (_str_contains(command->command[command->redirpos[i]],APD))
				command->redirorder[i] = ft_strdup(">>");
			else if (command->command[command->redirpos[i]][0] == '<')
				command->redirorder[i] = ft_strdup("<");
			else if (command->command[command->redirpos[i]][0] == '>')
				command->redirorder[i] = ft_strdup(">");
		}	
		i++;
	}
	//PRUEBAS
	i = 0;
	while(command->redirorder[i])
	{
		printf("Estos son el orden de redirecciones %s\n",command->redirorder[i]);
		i++;
	}
	return (true);
}

bool count_check_redirs(t_command *command)
{
	int	i;
	int	poslvl;
	int	positions[200];

	i = 0;
	poslvl = 0;
	while (command->command[i])
	{
		if (command->command[i][0] != 39 && command->command[i][0] != 34)
		{
			if (char_is_redir(command->command[i][0]))
			{
				positions[poslvl] = i;
				poslvl++;
			}
		}
		i++;
	}
	command->redircnt = poslvl;
	ft_fill_positions_to_command(command, positions);
	if (check_and_manage_order(command))
		return (false);
	return (true);
}

bool	contains_redir(t_command *command)
{
	if (_contains(command->command, HDC))
		return (1);
	if (_contains(command->command, APD))
		return (2);
	if (_contains(command->command, REDIPT))
		return (3);
	if (_contains(command->command, REDOPT))
		return (4);
	return (0);
}

bool	manage_redir_symbols(t_command *command)
{
	if (contains_redir(command))
	{
		if (count_check_redirs(command))
			return (false);
	//	fprintf(stderr,"Manage reddir symbols");
		return (true);	
	}
	return (false);
}
