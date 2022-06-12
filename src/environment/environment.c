/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:17:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/12 15:41:04 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_duplicate_environment(char **str)
{
	char	**result;
	int		i;
	int		check;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "OLDPWD=", 7))
			check = 1;
	}
	if (check == 1)
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str)));
	else
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "OLDPWD=", 7))
			str++;
		if (str[i])
			result[i] = ft_strdup(str[i]);
	}
	result[i] = 0;
	return (result);
}
