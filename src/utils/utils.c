/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:50:08 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/27 18:09:17 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_create_first_oldpwd(t_msh_var *msh)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	msh->own_envp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 3));
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

bool	_contains(char **command, char *str)
{
	int	i;
	int	u;
	int	e;
	int	maxlength;

	i = -1;
	e = 0;
	maxlength = ft_strlen(str);
	while (command[++i])
	{
		u = -1;
		while (command[i][++u])
		{
			if (command[i][u] == str[e])
			{
				e++;
				if (e == maxlength)
					return (true);
			}
			else
				e = 0;
		}		
	}
	return (false);
}

bool	_str_contains(char *command, char *str)
{
	int	i;
	int	u;
	int	maxlength;

	i = 0;
	u = 0;
	maxlength = ft_strlen(str);
	while (command[i])
	{
		if (command[i] == str[u])
		{
			u++;
			if (u == maxlength)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

bool	_str_exactly_contains(char *command, char *str)
{
	int	i;
	int	u;
	int	maxlength;
	int	mlength;

	i = 0;
	u = 0;
	if (!str || !command)
		return (false);
	maxlength = ft_strlen(str);
	mlength = ft_strlen(command);
	while (command[i])
	{
		if (command[i] == str[u])
		{
			u++;
			if (u == maxlength && mlength == maxlength)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

void	string_to_lower(char *pnt)
{
	int		i;
	char	aux;

	i = 0;
	while (pnt && pnt[i])
	{
		aux = ft_tolower(pnt[i]);
		pnt[i] = aux;
		i++;
	}
}
