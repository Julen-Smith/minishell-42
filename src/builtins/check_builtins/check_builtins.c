/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:50:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/07 19:44:09 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	ft_parent_builtin(t_command *command, t_msh_var *msh)
{
	if (!ft_strncmp(command->command[0], "cd", ft_strlen(command->command[0])))
	{
		ft_cd(command, msh);
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "export",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_export_check(command, msh);
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "unset",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_check_unset(command, msh);
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "exit",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_exit(command);
		return (false);
	}
	return (true);
}

bool	ft_child_builtin(t_command *command, t_msh_var *msh)
{
	if (!ft_strncmp(command->command[0], "echo",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_echo(command);
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "pwd",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_pwd();
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "env",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_env(msh, command);
		return (false);
	}
	return (true);
}
