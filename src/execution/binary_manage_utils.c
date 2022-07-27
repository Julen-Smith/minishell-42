/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_manage_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:15:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/27 18:25:35 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isfinal(t_command_table *table, int i, int count, t_msh_var *msh)
{
	ft_isexit(table, i, count);
	ft_parent_builtin(&table->commands[i],
		msh, count, i);
	ft_free_commands(table);
	return (true);
}

char	*ft_get_result(t_command *command, int i)
{
	char	*result;

	result = ft_strdup(command->path[i]);
	ft_doublefree(command->path);
	return (result);
}
