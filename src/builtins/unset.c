/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:21:27 by aalvarez          #+#    #+#             */
/*   Updated: 2022/08/02 16:09:06 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_not_env(char *variable, t_msh_var *msh)
{
	int	i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], variable, (ft_strlen(variable))))
			return (false);
	}
	return (true);
}

static void	ft_unset(char *variable, t_msh_var *msh)
{
	char	**tmp;
	int		i;
	int		x;

	if (ft_not_env(variable, msh))
		return ;
	else
	{
		tmp = ft_doublestrdup(msh->own_envp);
		ft_doublefree(msh->own_envp);
		msh->own_envp = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp)));
		i = -1;
		x = -1;
		while (tmp[++i])
		{
			if (ft_strncmp(tmp[i], variable, ft_strlen(variable)))
				msh->own_envp[++x] = ft_strdup(tmp[i]);
		}
		msh->own_envp[x + 1] = 0;
	}
	ft_doublefree(tmp);
}

bool	ft_check_unset(t_command *command, t_msh_var *msh, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (command->command[1])
	{
		i = 0;
		while (command->command[++i])
		{
			if (ft_check_variable(command->command[i]))
				ft_unset(command->command[i], msh);
		}
	}
	g_exit_status = 0;
	return (0);
}
