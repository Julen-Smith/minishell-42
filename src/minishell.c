/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/16 16:30:24 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			if (ft_check_dollars(table, i, x, msh))
			{
				x = 0;
				continue ;
			}
			x++;
		}
		if (manage_redir_symbols(&table->commands[i]))
			return (ERR_REDDIR);
	}
	return (1);
}

bool	ft_check_commands(t_command_table *table, t_msh_var *msh)
{
	int	i;

	i = -1;
	while (++i < table->cmd_count)
		if (!ft_parent_builtin(&table->commands[i], msh))
			return (true);
	return (false);
}

void	ft_start_program(char *str, t_command_table *table, t_msh_var *msh)
{
	if (!ft_error_print(parser(str, table)))
		if (!ft_error_print(lexer(table, msh)))
			if (!ft_check_commands(table, msh))
				execute(table, msh);
}

void	minishell(t_msh_var *msh)
{	
	char			*str;
	t_command_table	table;

	while (true)
	{
		str = readline(MSH);
		if (!str)
			ft_signal_exit();
		if (ft_strlen(str) > 0 && str[0] > 32)
		{
			str = added_pipe(str);
			if (!(ft_strlen(str) > 0) || str == NULL)
			{
				ft_error_print(ERR_PIPE);
				if (str != NULL)
					free(str);
				continue ;
			}	
			add_history(str);
			ft_start_program(str, &table, msh);
		}
		if (str != NULL)
			free(str);
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_msh_var			var;

	(void) argc;
	(void) argv;
	ft_interactive(1);
	ft_signals();
	var.own_envp = ft_duplicate_environment(environ);
	g_exit_status = 0;
	minishell(&var);
	return (0);
}
