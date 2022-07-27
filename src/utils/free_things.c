/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:38:16 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/27 16:44:29 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_and_liberate_execution(t_command_table *table, t_msh_var *msh)
{
	int	i;

	i = -1;
	close(table->unipipe);
	if (table->cmd_count > 1)
		free(table->pi);
	while (++i < table->cmd_count)
	{
		if (table->commands[i].is_absolute)
			ft_doublefree(table->commands[i].path);
	}
	ft_free_commands(table);
}

void	ft_freedollar_struct(t_dollars *dollars)
{
	free(dollars->beg);
	free(dollars->final);
	free(dollars->value);
	free(dollars->result);
}
