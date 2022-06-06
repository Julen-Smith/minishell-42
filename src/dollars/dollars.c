/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:19:51 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/06 21:23:59 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	ft_dollar_expansion(t_command *com, t_msh_var *msh, int a_n, int xref)
{
	char	*beg;
	char	*final;
	char	*value;
	char	*result;

	value = ft_dollar_value(com, msh, a_n, xref);
	beg = ft_substr(com->command[a_n], 0, xref);
	xref++;
	if (com->command[a_n][xref] != '$')
	{
		while (com->command[a_n][xref] && (com->command[a_n][xref] != ' '
				&& com->command[a_n][xref] != '$'
					&& com->command[a_n][xref] != '\''))
			xref++;
	}
	else
		xref++;
	if (xref < ft_strlen(com->command[a_n])
		|| com->command[a_n][xref - 1] == '"')
	{
		if (xref < ft_strlen(com->command[a_n]))
			final = ft_substr(com->command[a_n], xref,
					(ft_strlen(com->command[a_n]) - xref));
		else if (com->command[a_n][xref - 1] == '"')
			final = ft_strdup("\"");
	}
	if (beg[0])
	{
		if (value)
		{
			result = ft_strjoin(beg, value);
			free(beg);
			if (xref < ft_strlen(com->command[a_n])
				|| com->command[a_n][xref - 1] == '"')
			{
				if (com->command[a_n][xref - 1] == '"')
					beg = ft_strjoin(result, "\"");
				else
				{
					beg = ft_strjoin(result, final);
					free(final);
				}
				free(result);
				result = ft_strdup(beg);
				free(beg);
			}
		}
		else if (xref < ft_strlen(com->command[a_n])
			|| com->command[a_n][xref - 1] == '"')
		{
			result = ft_strjoin(beg, final);
			free(final);
			free(beg);
		}
	}
	else
	{
		if (value)
		{
			free(beg);
			beg = ft_strdup(value);
			if (xref < ft_strlen(com->command[a_n]))
				result = ft_strjoin(beg, final);
			else
				result = ft_strdup(beg);
		}
		else
			result = ft_strdup("");
	}
	free(com->command[a_n]);
	com->command[a_n] = ft_strdup(result);
	free(value);
	free(result);
}

int	ft_single_dollar(t_command *com, int a_n, int x)
{
	if (!com->command[a_n][x + 1] && com->command[a_n][x + 1] != '\''
			&& com->command[a_n][x + 1] != '"'
				&& com->command[a_n][x + 1] != ' ')
		return (1);
	return (0);
}
