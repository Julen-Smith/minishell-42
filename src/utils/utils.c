/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:50:08 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/07 11:42:13 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	_contains(char **command, char *str)
{
	int	i;
	int	u;
	int	e;
	int	maxlength;

	i = 0;
	u = 0;
	e = 0;
	maxlength = ft_strlen(str);
	while (command[i])
	{
		u = 0;
		while (command[i][u])
		{
			if (command[i][u] == str[e])
			{
				e++;
				if (e == maxlength)
					return (true);
			}
			else
				e = 0;
			u++;
		}		
		i++;
	}
	return (false);
}

bool _str_contains(char *command, char *str)
{
	int i;
	int u;
	int maxlength;

	i = 0;
	u = 0;
	maxlength = ft_strlen(str);
	while(command[i])
	{
		if (command[i] == str[u])
		{
			u++;
			if (u == maxlength)
				return (true);
		}
		else
			u = 0;	
		i++;
	}
	return (false);
}
