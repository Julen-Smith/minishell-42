/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:16:32 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/07 13:16:41 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_msh_var *msh)
{
	int		i;
	char	*pwd;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "PWD=", 4))
		{
			pwd = ft_substr(msh->own_envp[i], 4, ft_strlen(msh->own_envp[i]) - 4);
			printf("%s\n", pwd);
			free(pwd);
		}
	}
}