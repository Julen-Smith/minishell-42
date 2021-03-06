/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:25:00 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/19 18:47:02 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	clean_double_pipes(char *str)
{
	int	i;
	int	bef_char;

	i = 1;
	bef_char = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[bef_char] == '|')
			return (true);
		i++;
		bef_char++;
	}
	return (false);
}
