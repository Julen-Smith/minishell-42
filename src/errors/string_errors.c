/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:05:32 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/08 21:37:28 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Falta acortarla por dios */
int	process_string_marks(char *not_processed_cmd)
{	
	int		i;
	char	mark_type;
	int		quote_nbr;
	int		oposite_quote_nbr;
	char	oposite;
	int		length;

	i = 0;
	quote_nbr = 0;
	oposite_quote_nbr = 0;
	mark_type = 0;
	while (not_processed_cmd[i])
	{
		if (not_processed_cmd[i] == 39)
		{
			mark_type = 39;
			break ;
		}
		if (not_processed_cmd[i] == 34)
		{
			mark_type = 34;
			break ;
		}
		i++;
	}
	oposite = 39;
	if (mark_type == 39)
		oposite = 34;
	length = ft_strlen(not_processed_cmd);
	while (i != length)
	{	
		if (not_processed_cmd[i] == mark_type)
		{	
			quote_nbr++;
			i++;
			while (i != length && not_processed_cmd[i] != mark_type)
				i++;
			if (i == length && not_processed_cmd[i] != mark_type)
				return (true);
			else if (not_processed_cmd[i] == mark_type)
				quote_nbr++;
		}
		else if (not_processed_cmd[i] == oposite)
		{
			oposite_quote_nbr++;
			i++;
			while (i != length && not_processed_cmd[i] != oposite)
				i++;
			if (i == length && not_processed_cmd[i] != oposite)
				return (true);
			else if (not_processed_cmd[i] == oposite)
				oposite_quote_nbr++;
		}
		i++;
	}
	if (quote_nbr % 2 != 0 || oposite_quote_nbr % 2 != 0)
		return (true);
	return (false);
}
