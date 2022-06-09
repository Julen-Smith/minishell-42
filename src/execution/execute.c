/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/09 08:21:02 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


bool return_binary_path(const char *bin_path, char *binary_check)
{
	DIR *dp;
    struct dirent *dirp;
	
	dp = opendir(bin_path);
	dirp = readdir(dp);
	while (dirp != NULL)
	{
		if (_str_contains(dirp->d_name, binary_check))
		{
			closedir(dp);
			return(true);
		}
		dirp = readdir(dp);
	}
	closedir(dp);
	return (false);
}


char *reach_bin_path(char **command, t_msh_var *msh)
{
	if (return_binary_path(BIN,command[0]))
		return ((char *)BIN);
	if (return_binary_path(SBIN,command[0]))
		return ((char *)SBIN);
	//Ejecución de pwd
	//if(return_binary_path(msh->pwd,command[0]))
	//	return (msh->pwd);
	return (NULL);
}

bool gather_bin_path(t_command_table *table, t_msh_var * msh)
{
	int i;
	char *bin_path;

	i = 0;
	while (i != table->cmd_count)
	{
		bin_path = reach_bin_path(table->commands[i].command, msh);
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


void *execute(t_command_table *table, t_msh_var * msh)
{		
	int  i;
	int pi[2];
	int pe[2];
	pid_t pid;
	
	i = 0;
	if (gather_bin_path(table,msh))
		return (NULL);
	while (i != table->cmd_count)
	{
		pipe(pi);
		pipe(pe);
		pid = fork();
		if (pid == 0)
		{
			execve(ft_strjoin(table->commands[i].bin_path,table->commands[i].command[0]),table->commands[i].command, msh->own_envp);
			perror("Error");
		}
		else
			wait(0);
		i++;
	}
		

	return (NULL);
}


//DEAD CODE
	/*
	//char *args[] = {"ls", NULL, "/", 0};
	char	*ex;
	//ex = ft_deletechar(table->commands[i].command[0], 39);
	i = 0;
	//manage_reddir();
	while(i != table->cmd_count)
	{
		//if (table->cmd_count == 1)
		//	execute_lonely_command();	
		pipe(pi);
		pipe(pe);
		pid = fork();				
		if (pid == 0)
		{	
			printf("");
			if(access(table->commands[i].command[0],X_OK))
				execve(table->commands[i].command[0],table->commands[i].command, msh->own_envp);
			perror("This is not a valid path");
		}
		else
			wait(0);			
		i++;	
	}
	*/