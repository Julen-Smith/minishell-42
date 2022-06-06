/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:21:11 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 21:17:37 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	last_chr_not_pipe(char *str)
{
	int		i;
	char	last_chr;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32)
			last_chr = str[i];
		i++;
	}
	if (last_chr == '|')
		return (true);
	return (false);
}

int	ft_count_pipes(char *pnt)
{
	int	i;
	int	quote;
	int	pipecount;

	i = 0;
	pipecount = 0;
	while (pnt[i])
	{
		if (pnt[i] == 34 || pnt[i] == 39)
		{
			quote = pnt[i];
			i++;
			while (pnt[i] != quote)
				i++;
		}	
		if (pnt[i] == 124)
			pipecount++;
		i++;
	}
	return (pipecount);
}

void	generate_command_table(char *str, int cmd_count, t_command_table *table)
{
	int		i;
	int		u;
	char	**split;

	i = 0;
	table->commands = (t_command *) malloc(sizeof(t_command) * cmd_count);
	split = mini_split(str, '|');
	while (split[i])
	{
		table->commands[i].command = mini_split(split[i], ' ');
		u = 0;
		while (table->commands[i].command[u])
			u++;
		i++;
	}
}

/* Cleans de str and puts in to command table*/
int	parser(char *str, t_command_table *table)
{
	int		cmd_nbr;
	char	**split;

	if (last_chr_not_pipe(str))
		return (ERR_FINALPIPE);
	if (process_string_marks(str))
		return (ERR_QUOTATION);
	cmd_nbr = ft_count_pipes(str) + 1;
	generate_command_table(str, cmd_nbr, table);
	table->cmd_count = cmd_nbr;
	return (SUCCESS);
}
