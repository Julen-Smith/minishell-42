/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 05:38:45 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/27 17:29:37 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skipquotes(char *s, char c, char quote)
{
	while (*s && *s != c)
	{
		if (*s && *s == 34 || *s == 39)
		{
			quote = *s;
			if (s + 1)
				s++;
			while (*s && *s != quote)
				s++;
		}
		s++;
	}
	return (s);
}

char	*ft_skip_quotes_size(char *s, char quote)
{
	quote = *s;
	if (s + 1)
		s++;
	while (*s && *s != quote)
		s++;
	if (s + 1)
		s++;
	return (s);
}

char	*ft_create_pnt(char *s, char quote, char *pnt, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] && s[i] == 34 || s[i] == 39)
		{
			pnt[i] = s[i];
			quote = s[i];
			if (s[i + 1])
				i++;
			while (s[i] && s[i] != quote)
			{
				pnt[i] = s[i];
				i++;
			}	
		}
		pnt[i] = s[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
