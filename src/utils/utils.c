/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:50:08 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 21:09:39 by aalvarez         ###   ########.fr       */
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
