/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/11 18:02:59 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

void dup_son_choose(int i,t_command_table *table)
{
	if (table->cmd_count == 0)
	{
		dup2(table->pi[1],1);
		close(table->pi[0]);
	}
	else if (i == table->cmd_count -1)
	{
		
		if (table->cmd_count == 2)
		{
			dup2(table->pi[0],0);
			close(table->pi[1]);
		}
		else
		{
			dup2(table->unipipe,0);
			close(table->pi[1]);
		}
	}
	else
	{
		dup2(table->unipipe,0);
		dup2(table->pi[1],1);
		close(table->pi[0]);
	}
}

void father_fd_closes(t_command_table *table)
{
	if (table->cmd_count > 2)
	{
		table->unipipe = dup(table->pi[0]); // 5
		pipe(table->pi);
	}else
		close(table->pi[1]);
}

void *execute(t_command_table *table, t_msh_var * msh)
{	
	
	int  i;
	pid_t pid;
	
	table->pi =  malloc(sizeof(int) * 2);
	i = 0;
	if (gather_bin_path(table,msh))
		return (NULL);
	//printf("Numero de comandos %d\n",table->cmd_count);
	pipe(table->pi);
	while (i != table->cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			dup_son_choose(i,table);
			execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",table->commands[i].command[0])),table->commands[i].command, msh->own_envp);
			//perror("Error");
		}
		else
		{
			close(table->pi[1]);
			wait(0);
			father_fd_closes(table);
			/*
			if (i != 0 && i != table->cmd_count - 1)
			{
				close(table->pi[0]);
				close(table->pi[1]);
				pipe(table->pi);
				dup2(table->pi[1],table->unipipe);
				close(table->unipipe);		
			}
			*/
				
		}
		
		i++;
	}

	return (NULL);
	
}


//DEAD CODE 2
		 /*
		pid = fork();
		if (pid == 0)
		{	
			//dup2(table->pi[1],1);
			//close(pi[0]);
			dup_son_choose(pi,pe,i,table);
			//repipe(pi,pe);
			execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",
			table->commands[i].command[0])),
			table->commands[i].command, msh->own_envp);
			perror("Error");
			exit(0);
		}
		else
		{
			i++;
			close(table->pi[1]);
			wait(0);
			dup_son_choose(pi,pe,i,table);
			//dup2(pi[0],0);
			execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",
				table->commands[i].command[0])),
				table->commands[i].command, msh->own_envp);
	
		}
		*/

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