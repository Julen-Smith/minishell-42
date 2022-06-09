/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/09 11:46:06 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void close_dups(int *pi, int *pe)
{
	close(pi[0]);
	close(pi[1]);
	close(pe[0]);
	close(pe[1]);	
}

void dup_choose(int *pi, int *pe, int i,t_command_table *table)
{
	if (i == 0)
		dup2(pi[1],1);
	else if (i == table->cmd_count)
		dup2(0,pe[0]);
	else
		dup2(pe[0],pi[1]);
	close_dups(pi,pe);
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
			//dup_choose(pi,pe,i,table);
		//	repipe(pi,pe);
			execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",
			table->commands[i].command[0])),
			table->commands[i].command, msh->own_envp);
			perror("Error");
		}
		else
			wait(0);
		
		i++;
	}
//	close_dups(pi,pe);
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