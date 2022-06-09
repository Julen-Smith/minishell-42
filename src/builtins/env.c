/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:06:20 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/09 20:47:58 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_msh_var *msh, t_command *command)
{
	int	i;

	if (!command->command[1])
	{
		i = -1;
		while (msh->own_envp[++i])
			printf("%s\n", msh->own_envp[i]);
		exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", command->command[1]);
		exit_status = 1;
	}
}
