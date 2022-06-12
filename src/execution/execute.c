/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 07:41:25 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/12 16:30:13 by aalvarez         ###   ########.fr       */
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
		table->unipipe = dup(table->pi[0]);
		pipe(table->pi);
	}
	else if (table->cmd_count != 1)
		close(table->pi[1]);
}

void	ft_execute_child(t_command_table *table, t_msh_var *msh, int i)
{
	char	*tmp;
	char	*tmp2;

	if (table->cmd_count != 1)
		dup_son_choose(i, table);
	if (!ft_child_builtin(&table->commands[i], msh))
		exit(0);
	if (gather_bin_path(table,msh))
		return ;
	tmp = ft_strjoin("/",table->commands[i].command[0]);
	tmp2 = ft_strjoin(table->commands[i].bin_path, tmp);
	free(tmp);
	if (!access(tmp2, X_OK))
		execve(tmp2, table->commands[i].command, msh->own_envp);
	free(tmp2);
	perror("Error");
}

void *execute(t_command_table *table, t_msh_var * msh)
{	
	
	int  i;
	pid_t pid;
	
	i = 0;
	if (table->cmd_count != 1)
	{
		table->pi = malloc(sizeof(int) * 2);
		pipe(table->pi);
	}
	while (i != table->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			ft_execute_child(table, msh, i);
		else
		{
			if (table->cmd_count != 1)
				close(table->pi[1]);
			wait(0);
			father_fd_closes(table);
		}
		i++;
	}
	return (NULL);
}
