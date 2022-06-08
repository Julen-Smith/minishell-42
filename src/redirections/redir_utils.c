/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:21:14 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/08 21:49:54 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

bool	check_last_token_is_redir(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (char_is_redir(command[i - 1][0]))
		return (true);
	return (false);
}

bool	manage_redir_symbols(t_command *command)
{
	if (contains_redir(command))
	{
		if (check_last_token_is_redir(command->command))
			return (true);
		if (count_check_redirs(command))
			return (true);
	//	fprintf(stderr,"Manage reddir symbols");
	}
	return (false);
}

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
	while (i != command->redircnt)
	{
		command->redirpos[i] = position_stack[i];
		i++;
	}
}
