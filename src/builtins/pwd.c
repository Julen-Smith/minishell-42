/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:16:32 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/09 20:51:53 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	exit_status = 0;
}
