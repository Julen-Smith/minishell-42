/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:40:36 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/06 09:21:15 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				fprintf(stderr,"Ejecuto lexer\n");
			//	if(!ftls
			//_error_print(lexer(&table, msh)))
			//		fprintf(2,"");
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