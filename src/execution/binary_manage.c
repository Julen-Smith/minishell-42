/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:16:49 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/13 00:58:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	gather_bin_path(t_command_table *table, t_msh_var *msh)
{
	int		i;
	char	*bin_path;

	i = 0;
	while (i != table->cmd_count)
	{
		bin_path = reach_bin_path(&table->commands[i], msh);
		if (bin_path != NULL)
			table->commands[i].bin_path = bin_path;
		else
		{
			printf("%s %s %s", "Minishell :", table->commands[i].command[0],
				CMDNT);
			g_exit_status = 127;
			return (true);
		}		
		i++;
	}
	return (false);
}

bool	return_binary_path(const char *bin_path, char *binary_check)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(bin_path);
	if (dp != NULL)
	{
		dirp = readdir(dp);
		while (dirp != NULL)
		{
			if (_str_exactly_contains(dirp->d_name, binary_check))
			{
				closedir(dp);
				return (true);
			}
			dirp = readdir(dp);
		}
		closedir(dp);
	}
	return (false);
}

char	**get_actual_path(t_msh_var *msh)
{
	char	**path;
	int		i;

	i = 0;
	while (msh->own_envp[++i])
	{
		if (_str_contains(msh->own_envp[i], "PATH="))
		{
			path = ft_split(ft_split(ft_strdup(msh->own_envp[i]), '=')[1], ':');
			return (path);
		}	
	}
	return (NULL);
}

//Distribución principal de la ejecución de comandos
char	*reach_bin_path(t_command *command, t_msh_var *msh)
{	
	int		i;
	char	*tmp;

	i = -1;
	command->path = get_actual_path(msh);
	command->is_absolute = false;
	string_to_lower(command->command[0]);
	while (command->command[++i])
	{
		if (command->command[i][ft_strlen(command->command[i])] == '"')
		{
			tmp = ft_strtrim(command->command[i], "\"");
			free(command->command[i]);
			command->command[i] = ft_strdup(tmp);
		}
		else
		{
			tmp = ft_strtrim(command->command[i], "'");
			free(command->command[i]);
			command->command[i] = ft_strdup(tmp);
		}
		free(tmp);
	}
	i = 0;
	if (command->path)
	{
		while (command->path[i])
		{
			if (return_binary_path(command->path[i], command->command[0]))
				return (command->path[i]);
			i++;
		}
		if (access(command->command[0], X_OK) == 0)
		{
			command->is_absolute = true;
			return (command->command[0]);
		}	
	}
	return (NULL);
}
