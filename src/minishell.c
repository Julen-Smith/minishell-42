/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/07 18:43:42 by jsmith           ###   ########.fr       */
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

bool	pipe_before_command(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] < 32)
		i++;
		if (str[i] && str[i] == '|')
			return (true);
	}
	return (false);
}

//if (pipe_before_command(str))
				//	return (str);
char	*added_pipe(char *str)
{	
	if (last_chr_not_pipe(str))
	{
		while (last_chr_not_pipe(str))
		{
			if (ft_strlen(str) > 0)
			{
				str = ft_strjoin(str, readline("> "));
			}
			else
				str = readline("> ");
		}
	}
	return (str);
}

// __attribute__((__unused))t_process_manager *manager
void	minishell(t_msh_var *msh,
	__attribute__((unused))t_process_manager *manager)
{	
	char			*str;
	t_command_table	table;

	while (true)
	{
		str = readline(MSH);
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
			if (!ft_error_print(parser(str, &table)))
				if (!ft_error_print(lexer(&table, msh)))
					if (!ft_check_commands(&table, msh))
						execute(&table, msh);
		}
		if (str != NULL)
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
	g_exit_status = 0;
	minishell(&var, &manager);
	return (0);
}
