/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/09 19:05:28 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void close_dups(int *pi, int *pe)
{
	close(pi[0]);
	close(pi[1]);
	close(pe[0]);
	close(pe[1]);	
}


/*
void dup_father_choose(int i,t_command_table *table)
{
	if (i == 0)
	{
	
	}	
	else if (i == table->cmd_count)
	{
		
	}
	else
		
}
*/

void dup_son_choose(int i,t_command_table *table)
{
	if (i == 0)
	{
		dup2(table->pi[1],1);
		close(table->pi[0]);
	}	
	else if (i == table->cmd_count - 1)
	{
		dup2(table->pi[0],0);
		close(table->pi[1]);
	}
	else
	{
		dup2(table->unipipe,table->pi[0]);
		close(table->pi[1]);
		close(table->unipipe);
		pipe(table->pi);
		dup2(table->pi[1],table->unipipe);
	}
}

void *execute(t_command_table *table, t_msh_var * msh)
{	
	
	int  i;
	//int pi[2];
	int pe[2];
	pid_t pid;
	
	(void) pe;
	table->pi =  malloc(sizeof(int) * 2);
	i = 0;
	if (gather_bin_path(table,msh))
		return (NULL);
	pipe(table->pi);
	//printf("Numero de comandos %d\n",table->cmd_count);
	while (i != table->cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			dup_son_choose(i,table);
			execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",
			table->commands[i].command[0])),
			table->commands[i].command, msh->own_envp);
			perror("Error");
			exit(0);
		}
		else
		{
			close(table->pi[1]);
			wait(0);
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