/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:50:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/09 20:58:06 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_parent_builtin(t_command *command, t_msh_var *msh)
{
	if (!ft_strncmp(command->command[0], "echo", ft_strlen(command->command[0])))
	{
		ft_echo(command);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "cd", ft_strlen(command->command[0])))
	{
		ft_cd(command, msh);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "pwd", ft_strlen(command->command[0])))
	{
		ft_pwd();
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "export", ft_strlen(command->command[0])))
	{
		ft_export_check(command, msh);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "unset", ft_strlen(command->command[0])))
	{
		ft_check_unset(command, msh);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "env", ft_strlen(command->command[0])))
	{
		ft_env(msh, command);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "exit", ft_strlen(command->command[0])))
	{
		ft_exit(command);
		return (0);
	}
	return (1);
}
