/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/28 12:59:46 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <termios.h>

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
		if (contains_redire(table->commands[i].command[x]))
				return (ERR_REDDIR);
	}
	return (1);
}

bool	ft_start_program(char *str, t_command_table *table, t_msh_var *msh)
{
	if (ft_check_errors(str))
		return (1);
	if (!ft_error_print(parser(str, table)))
	{
		if (!ft_error_print(lexer(table, msh)))
		{
			execute(table, msh);
			return (0);
		}
	}
	return (1);
}

void	minishell(t_msh_var *msh)
{	
	char			*str;
	char			*tmp;
	struct termios	ter;
	struct termios	prev;
	t_command_table	table;

	while (true)
	{
		tcgetattr(STDIN_FILENO, &prev);
		tcgetattr(STDIN_FILENO, &ter);
		ter.c_lflag &= ~(ECHOCTL | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &ter);
		ft_signals();
		tmp = readline(MSH);
		if (!tmp)
			ft_signal_exit();
		if (!tmp[0])
		{
			free(tmp);
			continue ;
		}
		str = ft_strtrim(tmp, " ");
		free(tmp);
		add_history(str);
		if (ft_strlen(str) > 0)
		{
			if (ft_start_program(str, &table, msh))
				continue ;
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &prev);
		if (str != NULL)
			free(str);
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_msh_var			var;

	(void) argc;
	(void) argv;
	var.own_envp = ft_duplicate_environment(environ);
	g_exit_status = 0;
	minishell(&var);
	return (0);
}
