/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:19:51 by aalvarez          #+#    #+#             */
/*   Updated: 2022/08/02 20:53:27 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_has_beg(t_dollars *dollars, t_command *cm, int an, int x)
{
	if (dollars->value)
		ft_valuebeg(dollars, cm, an, x);
	else if (x < ft_strlen(cm->command[an]) || cm->command[an][x - 1] == '"')
		dollars->result = ft_strjoin(dollars->beg, dollars->final);
	else
		dollars->result = ft_strjoin(dollars->beg, "");
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
		else if (dollars->final != NULL)
			dollars->result = ft_strjoin("", dollars->final);
	}
	free(com->command[a_n]);
	com->command[a_n] = ft_strdup(dollars->result);
}

void	ft_check_exceptions(t_command *com, t_dollars *d, int a_n, int xref)
{
	if (ft_check_char(com, a_n, xref, "$?@/:")
		&& (com->command[a_n][xref - 1] == '$'))
		d->final = ft_substr(com->command[a_n], (xref + 1),
				(ft_strlen(com->command[a_n]) - (xref + 1)));
	else
		d->final = ft_substr(com->command[a_n], xref,
				(ft_strlen(com->command[a_n]) - xref));
}

void	ft_dollar_expansion(t_command *com, t_msh_var *msh, int a_n, int xref)
{
	t_dollars	dollars;

	dollars.value = ft_dollar_value(com, msh, a_n, xref);
	dollars.beg = ft_substr(com->command[a_n], 0, xref);
	xref++;
	if (com->command[a_n][xref] != '$')
	{
		while (com->command[a_n][xref] &&
				!ft_check_char(com, a_n, xref, " \'$?@/:"))
			xref++;
	}
	else
		xref++;
	if (xref < ft_strlen(com->command[a_n])
		|| com->command[a_n][xref - 1] == '"')
	{
		if (xref < ft_strlen(com->command[a_n]))
			ft_check_exceptions(com, &dollars, a_n, xref);
		else if (com->command[a_n][xref - 1] == '"')
			dollars.final = ft_strdup("\"");
	}
	else
		dollars.final = ft_strdup("");
	ft_new_com(&dollars, com, a_n, xref);
	ft_freedollar_struct(&dollars);
}

bool	ft_check_dollars(t_command_table *table, int i, int x, t_msh_var *msh)
{
	int	len;

	len = ft_strlen(table->commands[i].command[x]) - 1;
	if (ft_strchr_pos(table->commands[i].command[x], '$') >= 0
			&& !ft_single_dollar(&table->commands[i], x,
				ft_strchr_pos(table->commands[i].command[x], '$')))
	{
		if (table->commands[i].command[x][0] == '\''
			&& table->commands[i].command[x][len] == '\'')
			return (false);
		ft_dollar_expansion(&table->commands[i], msh,
			x, ft_strchr_pos(table->commands[i].command[x], '$'));
		return (true);
	}
	return (false);
}
