/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 11:00:58 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dollar_expansion(t_command *command, t_msh_var *msh, int arr_n, int xref)
{
	char	*beg;

	printf("llego");
	beg = ft_substr(command->command[arr_n], 0, xref);
	printf("beggining: %s\n", beg);
	exit(0);
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
			if (strchr(table->commands[i].command[x], '$') && table->commands[i].command[x][0] != '\'')
			{
				printf("found it: %s\n", strchr(table->commands[i].command[x], '$'));
				ft_dollar_expansion(&table->commands[i], msh, x, strchr(table->commands[i].command[x], '$'));
			}
			x++;
		}
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
	


	return  (0);
}