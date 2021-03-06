/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:27:20 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/18 18:01:23 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	pipe_before_command(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			while (str[i] < 32)
			i++;
			if (str[i] && str[i] == '|')
				return (true);
		}
	}
	return (false);
}

char	*added_pipe(char *str)
{	
	if (str[0] == '|')
	{
		printf("Minishell: sytax error near unexpected token '|'\n");
		str = NULL;
	}
	if (last_chr_not_pipe(str))
	{
		while (last_chr_not_pipe(str))
		{
			if (ft_strlen(str) > 1)
				str = ft_strjoin(str, readline("> "));
			else
				str = readline("> ");
		}
	}
	return (str);
}
