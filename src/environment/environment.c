/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:17:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/09 20:27:23 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_duplicate_environment(char **str)
{
	char	**result;
	int		i;

	i = -1;
	result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str)));
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "OLDPWD=", 7))
			str++;
		result[i] = ft_strdup(str[i]);
	}
	result[i] = 0;
	return (result);
}
