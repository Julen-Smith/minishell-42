/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/08 12:42:08 by aalvarez         ###   ########.fr       */
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

static void	ft_getoldpwd(t_msh_var *msh, char *pwd)
{
	int		i;
	int		x;
	char	**tmp;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("OLDPWD=", pwd);
			return ;
		}
	}
	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	msh->own_envp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 2));
	i = -1;
	x = 0;
	while (tmp[++i])
	{
		msh->own_envp[x++] = ft_strdup(tmp[i]);
		if (!ft_strncmp(tmp[i], "PWD=", 4))
			msh->own_envp[++x] = ft_strjoin("OLDPWD=", pwd);
	}
	msh->own_envp[x] = 0;
	ft_doublefree(tmp);
}

void	ft_cd(t_command *command, t_msh_var *msh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!command->command[1])
	{
		ft_getoldpwd(msh, pwd);
		chdir("/");
		//ft_getnewpwd(msh, pwd);
	}
}

int	ft_parent_builtin(t_command *command, t_msh_var *msh) // commands are lacking exit status
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
		ft_pwd(msh);
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

void	ft_check_commands(t_command_table *table, t_msh_var *msh)
{
	int	i;
	int	x;
	int	status;

	status = 0;
	i = -1;
	while (++i < table->cmd_count)
	{
		if (ft_parent_builtin(&table->commands[i], msh))
			printf("is child builtin\n");
			//ft_execute();
		//at the moment it only executes parent builtins
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
