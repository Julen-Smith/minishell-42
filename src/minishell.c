/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 12:56:49 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

char	*ft_dollar_value(t_command *command, t_msh_var *msh, int arr_n, int xref)
{
	int		i;
	char	*find;
	char	*tmp;

	i = xref + 1;
	while (command->command[arr_n][i] && (command->command[arr_n][i] != ' ' && command->command[arr_n][i] != '$' && command->command[arr_n][i] != '"' && command->command[arr_n][i] != '\''))
		i++;
	tmp = ft_substr(command->command[arr_n], (xref + 1), (i - (xref + 1)));
	find = ft_strjoin(tmp, "=");
	free(tmp);
	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], find, ft_strlen(find)))
		{
			tmp = ft_substr(msh->own_envp[i], ft_strlen(find), (ft_strlen(msh->own_envp[i]) - ft_strlen(find)));
			free(find);
			return (tmp);
		}
	}
	free(find);
	return (NULL);
}

void	ft_dollar_expansion(t_command *command, t_msh_var *msh, int arr_n, int xref)
{
	char	*beg;
	char	*final;
	char	*value;
	char	*result;

	value = ft_dollar_value(command, msh, arr_n, xref);
	beg = ft_substr(command->command[arr_n], 0, xref);
	xref++;
	while (command->command[arr_n][xref] && (command->command[arr_n][xref] != ' ' && command->command[arr_n][xref] != '$' && command->command[arr_n][xref] != '\''))
		xref++;
	if (xref < ft_strlen(command->command[arr_n]) || command->command[arr_n][xref - 1] == '"')
	{
		if (xref < ft_strlen(command->command[arr_n]))
			final = ft_substr(command->command[arr_n], xref, (ft_strlen(command->command[arr_n]) - xref));
		else if (command->command[arr_n][xref - 1] == '"')
			final = ft_strdup("\"");
	}
	if (beg[0])
	{
		if (value)
		{
			result = ft_strjoin(beg, value);
			free(beg);
			if (xref < ft_strlen(command->command[arr_n]) || command->command[arr_n][xref - 1] == '"')
			{
				if (command->command[arr_n][xref - 1] == '"')
					beg = ft_strjoin(result, "\"");
				else
				{
					beg = ft_strjoin(result, final);
					free(final);
				}
				free(result);
				result = ft_strdup(beg);
			}
		}
		else if (xref < ft_strlen(command->command[arr_n]) || command->command[arr_n][xref - 1] == '"')
		{
			result = ft_strjoin(beg, final);
			free(final);
		}
		free(command->command[arr_n]);
	}
	else
	{
		if (value)
			result = ft_strdup(value);
		else
			result = ft_strdup("");
	}
	command->command[arr_n] = ft_strdup(result);
	free(value);
	free(beg);
	free(result);
}

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
			if (ft_strchr_pos(table->commands[i].command[x], '$') >= 0 && table->commands[i].command[x][0] != '\'')
			{
				ft_dollar_expansion(&table->commands[i], msh, x, ft_strchr_pos(table->commands[i].command[x], '$'));
				x = 0;
				continue ;
			}
			x++;
		}
		if(manage_redir_symbols(&table->commands[i]))
			return (ERR_REDDIR);
	}
	return (1);
}

// __attribute__((__unused))t_process_manager *manager
void minishell(t_msh_var *msh, __attribute__((unused))t_process_manager *manager)
{	
	char *str;
	t_command_table table;

	while(true)
	{
		str = readline(MSH);
		if (ft_strlen(str) > 0)
		{
			//UNSET PATH COMPROBAR
			add_history(str);
			if(!ft_error_print(parser(str, &table)))
				if(!ft_error_print(lexer(&table, msh)))
					fprintf(stderr,"Ejecuto lexer\n");
		}
		free(str);
	}
}

int main(int argc, char *argv[], char *environ[])
{
	t_msh_var var;
	t_process_manager manager;

	//Duplicate environ
	(void) argc;
	(void) argv;
	var.own_envp = ft_duplicate_environment(environ);
	minishell(&var, &manager);
	return(0);
}