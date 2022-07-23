/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_things.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:38:16 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/23 19:02:40 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freedollar_struct(t_dollars *dollars)
{
	free(dollars->beg);
	free(dollars->final);
	free(dollars->value);
	free(dollars->result);
}
