/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:32:43 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/23 19:10:43 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//need to unset oldpwd at start of minishell exec for linux environment
static void	ft_getoldpwd(t_msh_var *msh)
{
	int		i;
	char	*old;

	msh->oldpwd = getcwd(NULL, 0);
	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			old = ft_substr(msh->own_envp[i], 3,
					(ft_strlen(msh->own_envp[i]) - 3));
			if (!ft_strncmp(old, msh->own_envp[i - 1], ft_strlen(old)))
			{
				free(msh->own_envp[i]);
				msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			}
			free(old);
			return ;
		}
	}
	ft_create_first_oldpwd(msh);
}

static void	ft_getnewpwd(t_msh_var *msh)
{
	int		i;

	free(msh->pwd);
	msh->pwd = getcwd(NULL, 0);
	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "PWD=", 4))
		{
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("PWD=", msh->pwd);
			return ;
		}
	}
}

static void	ft_last_dir(t_msh_var *msh)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			free(tmp);
			ft_getoldpwd(msh);
			tmp = ft_substr(msh->own_envp[i], 7,
					ft_strlen(msh->own_envp[i]) - 7);
			printf("%s\n", tmp);
			chdir(tmp);
			free(tmp);
		}
	}
	if (!tmp)
	{
		free(tmp);
		printf("Minishell: cd: OLDPWD not set\n");
	}
	ft_getnewpwd(msh);
}

bool	ft_cd_with_arguments(t_command *command, t_msh_var *msh)
{
	if (chdir(command->command[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", command->command[1]);
		g_exit_status = 1;
		free(msh->pwd);
		return (true);
	}
	ft_getoldpwd(msh);
	chdir(command->command[1]);
	ft_getnewpwd(msh);
	return (false);
}

bool	ft_cd(t_command *command, t_msh_var *msh, int count)
{
	if (count != 1)
		return (true);
	msh->pwd = getcwd(NULL, 0);
	if (!command->command[1])
	{
		ft_getoldpwd(msh);
		chdir("/");
		ft_getnewpwd(msh);
	}
	else if (command->command[1][0] == '-' && !command->command[1][1])
		ft_last_dir(msh);
	else
	{
		if (ft_cd_with_arguments(command, msh))
			return (false);
	}
	free(msh->pwd);
	free(msh->oldpwd);
	g_exit_status = 0;
	return (false);
}
