/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:40:06 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/16 16:48:38 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	gather_redir_fds(t_command *command)
{
	int		i;
	int		fd_q;

	i = 0;
	fd_q = command->redircnt;
	command->fd_collection = malloc(sizeof(char *) * fd_q);
	while (i != command->redircnt)
	{
		if (i == 0)
		{
			command->fd_collection[i] = malloc (sizeof(char) * (ft_strlen
						(command->command[command->redirpos[i] - 1] + 1)));
			command->fd_collection[i]
				= ft_strdup(command->command[command->redirpos[i] - 1]);
		}
		command->fd_collection[i] = malloc (sizeof(char)
				* (ft_strlen(command->command[command->redirpos[i] + 1] +1)));
		command->fd_collection[i]
			= ft_strdup(command->command [command->redirpos[i] + 1]);
		i++;
	}
	return (true);
}

void	ft_check_redirs(t_command *command, int i)
{
	if (_str_contains(command->command[command->redirpos[i]], HDC))
		command->redirorder[i] = ft_strdup("<<");
	else if (_str_contains(command->command[command->redirpos[i]], APD))
		command->redirorder[i] = ft_strdup(">>");
	else if (command->command[command->redirpos[i]][0] == '<')
		command->redirorder[i] = ft_strdup("<");
	else if (command->command[command->redirpos[i]][0] == '>')
		command->redirorder[i] = ft_strdup(">");
}

bool	check_and_manage_order(t_command *command)
{
	int	i;

	i = 0;
	command->redirorder = malloc (sizeof (char *) * (command->redircnt + 1));
	command->redirorder[command->redircnt] = NULL;
	while (i != command->redircnt)
	{
		command->redirorder[i] = malloc (sizeof(char) * (2 + 1));
		command->redirorder[i][2] = '\0';
		i++;
	}
	i = 0;
	while (i != command->redircnt)
	{
		if (ft_strlen(command->command[command->redirpos[i]]) > 2)
			return (true);
		else
			ft_check_redirs(command, i);
		i++;
	}
	gather_redir_fds(command);
	return (false);
}

bool	count_check_redirs(t_command *command)
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
		return (true);
	return (false);
}
