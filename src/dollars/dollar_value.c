/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:54:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/06 21:57:24 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_check_value(t_msh_var *msh, char *find, char *tmp)
{
	int	i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], find, ft_strlen(find)))
		{
			tmp = ft_substr(msh->own_envp[i], ft_strlen(find),
					(ft_strlen(msh->own_envp[i]) - ft_strlen(find)));
			free(find);
			return (tmp);
		}
	}
	free(find);
	return (NULL);
}

char	*ft_dollar_value(t_command *com, t_msh_var *msh, int a_n, int xref)
{
	int		i;
	char	*find;
	char	*tmp;

	i = xref + 1;
	if (com->command[a_n][i] == ' ' || com->command[a_n][i] == '"'
			|| com->command[a_n][i] == '\'' || com->command[a_n][i] == '$')
	{
		if (com->command[a_n][i] == '$')
			return (NULL);
		else
			find = ft_strdup("$");
		return (find);
	}
	while (com->command[a_n][i] && (com->command[a_n][i] != ' '
			&& com->command[a_n][i] != '$' && com->command[a_n][i] != '"'
				&& com->command[a_n][i] != '\''))
		i++;
	tmp = ft_substr(com->command[a_n], (xref + 1), (i - (xref + 1)));
	find = ft_strjoin(tmp, "=");
	free(tmp);
	return (ft_check_value(msh, find, tmp));
}

int	ft_single_dollar(t_command *com, int a_n, int x)
{
	if (!com->command[a_n][x + 1] && com->command[a_n][x + 1] != '\''
			&& com->command[a_n][x + 1] != '"'
				&& com->command[a_n][x + 1] != ' ')
		return (1);
	return (0);
}
