/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:05:32 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/19 18:56:07 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_if_empty_command(char *str)
{
	int i;
	int length;
	//int u;
	
	i = 0;
	if (!str)
		return (false);
	length = ft_strlen(str);
	while (str[i])
	{
		if(ft_isalnum(str[i]))
			return (false);
		i++;	
	}
	return (true);
}

int	process_string_quotes(char *not_processed_cmd)
{	
	int		i;
	int		x;

	i = -1;
	if (!not_processed_cmd)
		not_processed_cmd = NULL;
	while (++i < ft_strlen(not_processed_cmd))
	{
		if (not_processed_cmd[i] == '\'' || not_processed_cmd[i] == '"')
		{
			x = i + 1;
			while (not_processed_cmd[x])
			{
				if (not_processed_cmd[x] == not_processed_cmd[i])
				{
					i = x;
					break ;
				}
				x++;
			}
			if (i == x)
				continue ;
			return (true);
		}
	}
	return (false);
}
