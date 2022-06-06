/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:03:35 by aalvarez          #+#    #+#             */
/*   Updated: 2021/09/26 12:14:20 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst || src)
	{
		if (dst > src)
		{
			while (len--)
				((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		}
		else
		{
			while (i < len)
			{
				((unsigned char *)dst)[i] = ((const char *)src)[i];
				i++;
			}
		}
		return (dst);
	}
	return (NULL);
}
