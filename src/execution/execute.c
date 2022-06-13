/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/13 12:42:18 by jsmith           ###   ########.fr       */
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
	
	int		i;
	pid_t	pid;
	int		status;
	
	table->pi =  malloc(sizeof(int) * 2);
	i = 0;
	if (gather_bin_path(table,msh))
		return (NULL);
	pipe(table->pi);
	while (i != table->cmd_count)
	{
		if (table->commands[i].redir_exist)
			execute_reddir(table->commands[i],msh);
		else	
			pid = fork();
			if (pid == 0)
			{
				dup_son_choose(i,table);
				if (!ft_child_builtin(&table->commands[i], msh))
					exit(0);
				else if (!access(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",table->commands[i].command[0])), X_OK))
					execve(ft_strjoin(table->commands[i].bin_path, ft_strjoin("/",table->commands[i].command[0])),table->commands[i].command, msh->own_envp);
				perror("Error");
			}
			else
			{
				close(table->pi[1]);
				wait(&status);
				exit_status = WEXITSTATUS(status);
				father_fd_closes(table);
			}
			i++;
		}
	return (NULL);
}
