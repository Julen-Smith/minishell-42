/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:16:49 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/16 18:16:01 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	gather_bin_path(t_command_table *table, t_msh_var *msh)
{
	int		i;
	char	*bin_path;

	i = 0;
	while (i != table->cmd_count)
	{
		bin_path = reach_bin_path(&table->commands[i], msh);
		if (bin_path != NULL)
		{
			table->commands[i].bin_path = ft_strdup(bin_path);
			free(bin_path);
		}
		else
		{
			free(bin_path);
			table->commands[i].bin_path = NULL;
			printf("%s %s %s", "Minishell :", table->commands[i].command[0],
				CMDNT);
			g_exit_status = 127;
			return (true);
		}		
		i++;
	}
	return (false);
}

bool	return_binary_path(const char *bin_path, char *binary_check)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(bin_path);
	if (dp != NULL)
	{
		dirp = readdir(dp);
		while (dirp != NULL)
		{
			if (_str_exactly_contains(dirp->d_name, binary_check))
			{
				closedir(dp);
				return (true);
			}
			dirp = readdir(dp);
		}
		closedir(dp);
	}
	return (false);
}

char	**get_actual_path(t_msh_var *msh)
{
	char	**path;
	char	*tmp;
	char	**tmp2;
	int		i;

	i = 0;
	while (msh->own_envp[++i])
	{
		if (_str_contains(msh->own_envp[i], "PATH="))
		{
			tmp = ft_strdup(msh->own_envp[i]);
			tmp2 = ft_split(tmp, '=');
			path = ft_split(tmp2[1], ':');
			free(tmp);
			ft_doublefree(tmp2);
			return (path);
		}	
	}
	return (NULL);
}

void	ft_quotetrim(t_command *command, int i, int final, int j)
{
	char	**str;
	char	*tmp;
	char	*pre;

	pre = ft_substr(command->command[i], 0, j);
	tmp = ft_substr(command->command[i], (j + 1), (final - (j + 1)));
	if (pre[0])
	{
		str = (char **)malloc(sizeof(char *) * 4);
		str[0] = ft_strdup(pre);
		str[1] = ft_strdup(tmp);
		free(tmp);
		str[2] = ft_substr(command->command[i], (final + 1),
					ft_strlen(command->command[i]) - (final + 1));
		str[3] = 0;
		tmp = ft_strjoin(str[0], str[1]);
		free(command->command[i]);
		command->command[i] = ft_strjoin(tmp, str[2]);
	}
	else
	{
		str = (char **)malloc(sizeof(char *) * 3);
		str[0] = ft_strdup(tmp);
		str[1] = ft_substr(command->command[i], (final + 1),
					ft_strlen(command->command[i]) - (final + 1));
		str[2] = 0;
		free(command->command[i]);
		if (!str[0][0] && !str[1][0])
			command->command[i] = ft_strdup("");
		else
			command->command[i] = ft_strjoin(str[0], str[1]);
	}
	ft_doublefree(str);
	free(pre);
	free(tmp);
}

void	ft_trim_algorithm(t_command *command, int i)
{
	int		j;
	int		final;

	j = 0;
	while (command->command[i][j])
	{
		if (command->command[i][j] == '"' || command->command[i][j] == '\'')
		{
			final = j + 1;
			while (command->command[i][final] && command->command[i][final]
					!= command->command[i][j])
				final++;
			ft_quotetrim(command, i, final, j);
			if (final >= ft_strlen(command->command[i]))
				return ;
			j = final - 1;
			continue ;
		}
		j++;
	}
}

//Distribución principal de la ejecución de comandos
char	*reach_bin_path(t_command *command, t_msh_var *msh)
{	
	int		i;
	char	*result;

	command->path = get_actual_path(msh);
	command->is_absolute = false;
	string_to_lower(command->command[0]);
	i = -1;
	while (command->command[++i])
		ft_trim_algorithm(command, i);
	i = 0;
	if (command->path)
	{
		while (command->path[i])
		{
			if (return_binary_path(command->path[i], command->command[0]))
			{
				result = ft_strdup(command->path[i]);
				ft_doublefree(command->path);
				return (result);
			}
			i++;
		}
		if (access(command->command[0], X_OK) == 0)
		{
			command->is_absolute = true;
			return (command->command[0]);
		}	
	}
	ft_doublefree(command->path);
	return (NULL);
}
