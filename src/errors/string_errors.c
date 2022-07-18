/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:05:32 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/18 05:24:35 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_string_quotes(char *not_processed_cmd)
{	
	int		i;
	int		x;

	i = -1;
	while (++i < ft_strlen(not_processed_cmd))
	{
		if (not_processed_cmd[i] == '\'' || not_processed_cmd[i] == '"')
		{
			x = i + 1;
			while (not_processed_cmd[x])
			{
				if (not_processed_cmd[x] == not_processed_cmd[i])
				{
					i = x + 1;
					break ;
				}
				x++;
			}
			if (i == x + 1)
				continue ;
			return (true);
		}
	}
	return (false);
}
