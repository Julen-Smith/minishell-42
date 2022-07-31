/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:32:43 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/31 13:23:51by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_home(t_msh_var *msh)
{
	int	i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "HOME=", 5))
			return (ft_substr(msh->own_envp[i], 5, ft_strlen(msh->own_envp[i]) - 5));
	}
	printf("HOME not set\n");
	return (NULL);
}

void	ft_firstoldpwd(t_msh_var *msh)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	msh->own_envp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 2));
	while (tmp[++i])
	{
		if (!ft_strncmp(tmp[i], "PWD=", 4))
		{
			msh->own_envp[j] = ft_strjoin("OLDPWD=", msh->oldpwd);
			j++;
		}
		msh->own_envp[j++] = ft_strdup(tmp[i]);
	}
	msh->own_envp[j] = 0;
	ft_doublefree(tmp);
}

void	ft_getoldpwd(t_msh_var *msh, char *route)
{
	int		i;
	char	*tmp;

	i = -1;
	msh->oldpwd = getcwd(NULL, 0);
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("PWD=", route);
			if (ft_strncmp(msh->own_envp[i + 1], tmp, ft_strlen(tmp)))
			{
				free(msh->own_envp[i]);
				msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			}
			free(tmp);
			return ;
		}
	}
	ft_firstoldpwd(msh);
}

void	ft_getnewpwd(t_msh_var *msh)
{
	int	i;

	i = -1;
	msh->pwd = getcwd(NULL, 0);
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "PWD=", 4))
		{
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("PWD=", msh->pwd);
		}
	}
}

void	ft_previous_dir(t_msh_var *msh)
{
	int		i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			msh->oldpwd = ft_substr(msh->own_envp[i + 1], 4, (ft_strlen(msh->own_envp[i + 1]) - 4));
			free(msh->own_envp[i + 1]);
			msh->pwd = ft_substr(msh->own_envp[i], 7, (ft_strlen(msh->own_envp[i]) - 7));
			chdir(msh->pwd);
			msh->own_envp[i + 1] = ft_strjoin("PWD=", msh->pwd);
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			return ;
		}
	}
	printf("Minishell: cd: OLDPWD not set\n");
	msh->oldpwd = NULL;
	msh->pwd = NULL;
}

bool	ft_cd(t_command *command, t_msh_var *msh, int count)
{
	char	*home;

	if (count != 1)
		return (true);
	if (!command->command[1] || command->command[1][0] == '~')
	{
		home = ft_get_home(msh);
		ft_getoldpwd(msh, home);
		chdir(home);
		ft_getnewpwd(msh);
		free(home);
	}
	else if (command->command[1][0] == '-')
		ft_previous_dir(msh);
	else
	{
		ft_getoldpwd(msh, command->command[1]);
		if (chdir(command->command[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", command->command[1]);
			g_exit_status = 1;
			free(msh->oldpwd);
			return (false);
		}
		chdir(command->command[1]);
		ft_getnewpwd(msh);
	}
	free(msh->oldpwd);
	free(msh->pwd);
	g_exit_status = 0;
	return (false);
}
