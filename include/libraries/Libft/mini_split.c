/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:23:39 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 10:35:13 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static char	**ft_free(char **p, size_t count)
{
	size_t	i;

	if (p)
	{
		i = 0;
		while (i < count)
		{
			if (p[i] != NULL)
				free(p[i]);
			i++;
		}
		free (p);
	}
	return (NULL);
}

size_t	ft_count_size(const char	*s, char c)
{
	size_t	i;
	char quote;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if(*s && *s == 34 || *s == 39)
			{
				quote = *s;
				if (s+1)				
					s++;
				while(*s && *s != quote)
					s++;
				if (s+1)
				s++;
			}	
			i++;
			while (*s && *s != c)
				s++;
		}	
	}
	return (i);
}

static char	*ft_fill_each_pointer(char const *s, char c)
{
	char	*pnt;
	int		i;
	char 	quote;

	i = 0;
	while (s[i] && s[i] != c)
	{	
		if (s[i] && s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			if (s[i + 1])
				i++;
			while(s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	pnt = (char *) malloc((i + 1) * sizeof(char));
	if (!pnt)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] && s[i] == 34 || s[i] == 39)
		{
			pnt[i] = s[i];
			quote = s[i];
			if (s[i +1])
				i++;
			while(s[i] && s[i] != quote)
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

static char	**ft_fill_pointers(char const *s, char c, char **tab)
{
	int	i;
	char quote;

	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && *s != c)
		{
			tab[i] = ft_fill_each_pointer(s, c);
			if (!tab[i])
				return (ft_free(tab, i));
				/*
			
			*/
			i++;
			while (*s && *s != c)
			{
				if(*s && *s == 34 || *s == 39)
				{
					quote = *s;
					if (s+1)				
						s++;
					while(*s && *s != quote)
						s++;
				}
				s++;
			}
		}
	}
	tab[i] = NULL;
	
	return (tab);
}

char	**mini_split(char const *s, char c)
{
	int		size;
	char	**tab;

	if (s)
		size = ft_count_size(s, c);
	tab = malloc ((size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill_pointers(s, c, tab);
	return (tab);
}

