/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/07 13:44:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

int	lexer(t_command_table *table, t_msh_var *msh)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	while (++i < table->cmd_count)
	{
		x = 0;
		while (table->commands[i].command[x])
		{
			if (ft_strchr_pos(table->commands[i].command[x], '$') >= 0
				&& table->commands[i].command[x][0] != '\''
					&& !ft_single_dollar(&table->commands[i], x,
						ft_strchr_pos(table->commands[i].command[x], '$')))
			{
				ft_dollar_expansion(&table->commands[i], msh,
					x, ft_strchr_pos(table->commands[i].command[x], '$'));
				x = 0;
				continue ;
			}
			x++;
		}
		if (manage_redir_symbols(&table->commands[i]))
			return (ERR_REDDIR);
	}
	//
	i = -1;
	while (++i < table->cmd_count)
	{
		x = -1;
		while (table->commands[i].command[++x])
			printf("%s\n",table->commands[i].command[x]); // checking all the commands
	}
	//
	return (1);
}

void	ft_cd(t_command *command)
{
	
}

void	ft_parent_builtin(t_command *command, t_msh_var *msh) // commands are lacking exit status
{
	if (!ft_strncmp(command->command[0], "echo", 4))
		ft_echo(command);
	else if (!ft_strncmp(command->command[0], "cd", 2))
		ft_cd(command);
	else if (!ft_strncmp(command->command[0], "pwd", 3))
		ft_pwd(msh);
	/*else if (!ft_strncmp(command->command[0], "export", 6))
		ft_export();
	else if (!ft_strncmp(command->command[0], "unset", 5))
		ft_unset();*/
	else if (!ft_strncmp(command->command[0], "env", 3))
		ft_env(msh);
	else if (!ft_strncmp(command->command[0], "exit", 4))
		ft_exit();
}

void	ft_check_commands(t_command_table *table, t_msh_var *msh)
{
	int	i;
	int	x;
	int	status;

	status = 0;
	i = -1;
	while (++i < table->cmd_count)
	{
		//at the moment it only executes parent builtins
		ft_parent_builtin(&table->commands[i], msh);
	}
}

// __attribute__((__unused))t_process_manager *manager
void	minishell(t_msh_var *msh, __attribute__((unused))t_process_manager *manager)
{	
	char			*str;
	t_command_table	table;

	while (true)
	{
		str = readline(MSH);
		if (ft_strlen(str) > 0)
		{
			//UNSET PATH COMPROBAR
			add_history(str);
			if (!ft_error_print(parser(str, &table)))
			{
				if (!ft_error_print(lexer(&table, msh)))
					ft_check_commands(&table, msh);
					//fprintf(stderr, "Ejecuto lexer\n");
			}
		}
		free(str);
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_msh_var			var;
	t_process_manager	manager;

	(void) argc;
	(void) argv;
	var.own_envp = ft_duplicate_environment(environ);
	minishell(&var, &manager);
	return (0);
}
