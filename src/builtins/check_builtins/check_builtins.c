/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:50:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/08 21:56:16 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_parent_builtin(t_command *command, t_msh_var *msh)
{
	if (!ft_strncmp(command->command[0], "echo", 4))
	{
		ft_echo(command);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "cd", 2))
	{
		ft_cd(command, msh);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "pwd", 3))
	{
		ft_pwd();
		return (0);
	}
	/*else if (!ft_strncmp(command->command[0], "export", 6))
		ft_export();
	else if (!ft_strncmp(command->command[0], "unset", 5))
		ft_unset();*/
	else if (!ft_strncmp(command->command[0], "env", 3))
	{
		ft_env(msh);
		return (0);
	}
	else if (!ft_strncmp(command->command[0], "exit", 4))
	{
		ft_exit();
		return (0);
	}
	return (1);
}
