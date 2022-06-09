/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:43:31 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/08 21:58:12 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//need to unset oldpwd at start of minishell exec
static void	ft_getoldpwd(t_msh_var *msh)
{
	int		i;
	char	**tmp;

	msh->oldpwd = getcwd(NULL, 0);
	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7)
			&& ft_strncmp(msh->oldpwd, msh->pwd, ft_strlen(msh->oldpwd)))
		{
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			free(msh->pwd);
			return ;
		}
	}
	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	msh->own_envp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 2));
	i = -1;
	while (tmp[++i])
		msh->own_envp[i] = ft_strdup(tmp[i]);
	msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
	msh->own_envp[i + 1] = 0;
	free(msh->pwd);
	ft_doublefree(tmp);
}

static void	ft_getnewpwd(t_msh_var *msh)
{
	int		i;

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
	ft_getoldpwd(msh);
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			tmp = ft_substr(msh->own_envp[i], 7,
					ft_strlen(msh->own_envp[i]) - 7);
			chdir(tmp);
			free(tmp);
		}
	}
	ft_getnewpwd(msh);
}

void	ft_cd(t_command *command, t_msh_var *msh)
{
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
		if (!opendir(command->command[1]))
		{
			printf("cd: %s: No such file or directory\n", command->command[1]);
			return ;
		}
		ft_getoldpwd(msh);
		chdir(command->command[1]);
		ft_getnewpwd(msh);
	}
	free(msh->oldpwd);
}
