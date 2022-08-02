/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublefree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:06:47 by aalvarez          #+#    #+#             */
/*   Updated: 2022/08/02 17:17:00 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_doublefree(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str && str[i])
			free(str[i]);
	}
	if (str)
		free(str);
}
