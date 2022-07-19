/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/19 06:18:41 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lexer(t_command_table *table, t_msh_var *msh)
{
	int	i;
	int	x;

	i = -1;
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

void	ft_start_program(char *str, t_command_table *table, t_msh_var *msh)
{
	if (!ft_error_print(parser(str, table)))
		if (!ft_error_print(lexer(table, msh)))
			execute(table, msh);
}

void	minishell(t_msh_var *msh)
{	
	char			*str;
	char			*tmp;
	t_command_table	table;

	while (true)
	{
		tmp = readline(MSH);
		if (!tmp)
			ft_signal_exit();
		str = ft_strtrim(tmp, " ");
		free(tmp);
		add_history(str);
		if (ft_strlen(str) > 0)
		{
			str = added_pipe(str);
			if (str == NULL || !(ft_strlen(str) > 0))
			{
				ft_error_print(ERR_PIPE);
				if (str)
					free(str);
				continue ;
			}	
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
