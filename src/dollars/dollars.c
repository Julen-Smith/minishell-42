/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:19:51 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/10 11:30:03 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_has_beg(t_dollars *dollars, t_command *cm, int an, int x)
{
	if (dollars->value)
	{
		dollars->result = ft_strjoin(dollars->beg, dollars->value);
		free(dollars->beg);
		if (x < ft_strlen(cm->command[an])
			|| cm->command[an][x - 1] == '"')
		{
			if (cm->command[an][x - 1] == '"')
				dollars->beg = ft_strjoin(dollars->result, "\"");
			else
			{
				dollars->beg = ft_strjoin(dollars->result, dollars->final);
				free(dollars->final);
			}
			free(dollars->result);
			dollars->result = ft_strdup(dollars->beg);
			free(dollars->beg);
		}
	}
	else if (x < ft_strlen(cm->command[an]) || cm->command[an][x - 1] == '"')
	{
		dollars->result = ft_strjoin(dollars->beg, dollars->final);
		free(dollars->final);
		free(dollars->beg);
	}
}

static void	ft_new_com(t_dollars *dollars, t_command *com, int a_n, int xref)
{
	if (dollars->beg[0])
		ft_has_beg(dollars, com, a_n, xref);
	else
	{
		if (dollars->value)
		{
			free(dollars->beg);
			dollars->beg = ft_strdup(dollars->value);
			if (xref < ft_strlen(com->command[a_n]))
				dollars->result = ft_strjoin(dollars->beg, dollars->final);
			else
				dollars->result = ft_strdup(dollars->beg);
		}
		else
			dollars->result = ft_strdup("");
	}
	free(com->command[a_n]);
	com->command[a_n] = ft_strdup(dollars->result);
	free(dollars->value);
	free(dollars->result);
}

void	ft_dollar_expansion(t_command *com, t_msh_var *msh, int a_n, int xref)
{
	t_dollars	dollars;

	dollars.value = ft_dollar_value(com, msh, a_n, xref);
	dollars.beg = ft_substr(com->command[a_n], 0, xref);
	xref++;
	if (com->command[a_n][xref] != '$')
	{
		while (com->command[a_n][xref] && !ft_check_char(com, a_n, xref, " \'$?@"))
			xref++;
	}
	else
		xref++;
	if (xref < ft_strlen(com->command[a_n])
		|| com->command[a_n][xref - 1] == '"')
	{
		if (xref < ft_strlen(com->command[a_n]))
			dollars.final = ft_substr(com->command[a_n], xref,
					(ft_strlen(com->command[a_n]) - xref));
		else if (com->command[a_n][xref - 1] == '"')
			dollars.final = ft_strdup("\"");
	}
	ft_new_com(&dollars, com, a_n, xref);
}
