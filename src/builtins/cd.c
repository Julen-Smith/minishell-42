/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:49:49 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/15 09:50:13by ajsmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_create_first_oldpwd(t_msh_var *msh)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	msh->own_envp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 2));
	i = 0;
	j = -1;
	while (tmp[++j])
	{
		msh->own_envp[i++] = ft_strdup(tmp[j]);
		if (!ft_strncmp(tmp[j], "PWD=", 4))
			msh->own_envp[i++] = ft_strjoin("OLDPWD=", msh->oldpwd);
	}
	msh->own_envp[i] = 0;
	ft_doublefree(tmp);
}

//need to unset oldpwd at start of minishell exec
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
			old = ft_substr(msh->own_envp[i], 3, ft_strlen(msh->own_envp[i]));
			if (!ft_strncmp(old, msh->own_envp[i - 1], ft_strlen(old)))
				msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			return ;
		}
	}
	ft_create_first_oldpwd(msh);
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
			printf("%s\n", tmp);
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
			g_exit_status = 1;
			return ;
		}
		ft_getoldpwd(msh);
		chdir(command->command[1]);
		ft_getnewpwd(msh);
	}
	g_exit_status = 0;
}
