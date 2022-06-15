/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:17:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/15 09:55:57 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**return_heaped_env(int check, char **str)
{
	char	**result;

	if (check == 1)
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str)));
	else
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
	return (result);
}

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
	result = return_heaped_env(check, str);
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
