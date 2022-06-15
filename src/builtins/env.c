/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:06:20 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/15 09:46:07 by jsmith           ###   ########.fr       */
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
		g_exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", command->command[1]);
		g_exit_status = 1;
	}
}
