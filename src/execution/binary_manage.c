/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:16:49 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/09 13:17:43 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool gather_bin_path(t_command_table *table, t_msh_var * msh)
{
	int i;
	char *bin_path;

	i = 0;
	while (i != table->cmd_count)
	{
		bin_path = reach_bin_path(&table->commands[i], msh);
		if (bin_path != NULL)	
			table->commands[i].bin_path = bin_path;
		else
		{
			printf("%s %s", BAERR,CMDNT);
			return (true);
		}		
		i++;
	}
	return (false);
}

bool return_binary_path(const char *bin_path, char *binary_check)
{
	DIR *dp;
    struct dirent *dirp;
	
	dp = opendir(bin_path);
	if (dp != NULL)
	{
		dirp = readdir(dp);
		while (dirp != NULL)
		{
			if (_str_exactly_contains(dirp->d_name, binary_check))
			{
				closedir(dp);
				return(true);
			}
			dirp = readdir(dp);
		}
		closedir(dp);
	}
	return (false);
}

char **get_actual_path(t_msh_var *msh)
{
	char **path;
	int i;

	i = 0;
	while(msh->own_envp[++i])
		if (_str_contains(msh->own_envp[i],"PATH="))
		{
			path = ft_split(ft_split(ft_strdup(msh->own_envp[i]),'=')[1],':'); 
			return (path);	
		}
	return (NULL);
}

char *reach_bin_path(t_command *command, t_msh_var *msh)
{	
	int i;

	i = 0;
	
	command->path = get_actual_path(msh);
	if (command->path)
	{
		while (command->path[i])
		{
			if (return_binary_path(command->path[i],command->command[0]))
				return (command->path[i]);
			i++;
		}
		if (access(command->command[0],X_OK) == 0)
			return (command->command[0]);
	}
	//if ()
	//	;
	//if (return_binary_path(SBIN,command[0]))
	//	return ((char *)SBIN);
	
	//Ejecución de pwd
	//if(return_binary_path(msh->pwd,command[0]))
	//	return (msh->pwd);

	return (NULL);
}
