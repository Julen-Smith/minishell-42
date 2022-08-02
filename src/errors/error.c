/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:36:39 by jsmith            #+#    #+#             */
/*   Updated: 2022/08/02 21:07:06 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_next_next_errors(int errnumb)
{
	if (errnumb == ERR_FINALPIPE)
	{
		fprintf(stderr, "ERR : FINAL PIPE\n");
		return (true);
	}
	else if (errnumb == ERR_REDDIR)
	{
		fprintf(stderr, "ERR : REDDIRECTION ERROR\n");
		return (true);
	}
	else if (errnumb == ERR_EMPTY_PIPE)
	{
		fprintf(stderr, "ERR : EMPTY PIPE\n");
		return (true);
	}
	return (false);
}

bool	ft_next_errors(int errnumb)
{
	if (errnumb == ERR_QUOTATION)
	{
		fprintf(stderr, "ERR : QUOTATION\n");
		return (true);
	}
	else if (errnumb == ERR_INVALIDCHR)
	{
		fprintf(stderr, "ERR : INVALIDCHR\n");
		return (true);
	}
	else if (errnumb == ERR_COMMAND_404)
	{
		fprintf(stderr, "ERR : Command not found\n");
		return (true);
	}
	if (ft_next_next_errors(errnumb))
		return (true);
	return (false);
}

bool	ft_error_print(int errnumb)
{
	if (errnumb == ERR_NOT_WANNA_HANDLE)
	{
		fprintf(stderr, "ERR : NOTWANNAHANDLE\n");
		return (true);
	}
	else if (errnumb == ERR_SIGSMTHG)
	{
		fprintf(stderr, "ERR : SIGSMTHG\n");
		return (true);
	}
	else if (errnumb == ERR_UNDEFINED)
	{
		fprintf(stderr, "ERR : UNDEFINED\n");
		return (true);
	}
	else if (errnumb == ERR_UNKNOWN)
	{
		fprintf(stderr, "ERR : UKNOWN\n");
		return (true);
	}
	if (ft_next_errors(errnumb))
		return (true);
	return (false);
}

void	ft_free_commands(t_command_table *table)
{
	int	i;

	i = -1;
	while (++i < table->cmd_count && table->cmd_count)
	{
		if (table->commands[i].command)
			ft_doublefree(table->commands[i].command);
		table->commands[i].command = NULL;
		if (table->commands[i].bin_path)
		{
			//si metes el espacio raro lo que peta es esto de aqui
			free(table->commands[i].bin_path);
		}
		table->commands[i].bin_path = NULL;
	}
	if (!table->commands)
		return ;
	free(table->commands);
}

bool	ft_check_errors(char *str)
{
	str = added_pipe(str);
	if (str == NULL || !(ft_strlen(str) > 0))
	{
		ft_error_print(ERR_PIPE);
		if (str)
			free(str);
		return (1);
	}	
	return (0);
}
