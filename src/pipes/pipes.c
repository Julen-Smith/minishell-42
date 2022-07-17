/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:27:20 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/16 17:19:36 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	pipe_before_command(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] < 32)
		i++;
		if (str[i] && str[i] == '|')
			return (true);
	}
	return (false);
}

char	*added_pipe(char *str)
{	
	if (last_chr_not_pipe(str))
	{
		while (last_chr_not_pipe(str))
		{
			if (ft_strlen(str) > 0)
			{
				str = ft_strjoin(str, readline("> "));
			}
			else
				str = readline("> ");
		}
	}
	return (str);
}
