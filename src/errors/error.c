/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:36:39 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/08 13:23:17 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_error_print(int errnumb)
{
	if (errnumb == ERR_NOT_WANNA_HANDLE)
	{
		fprintf(stderr, "ERR : NOTWANNAHANDLE\n");
		return (true);
	}
	else if (errnumb == ERR_SIGSMTHG)
	{
		fprintf(stderr, "ERR : SIGSMTHG\n");
		return (true);
	}
	else if (errnumb == ERR_UNDEFINED)
	{
		fprintf(stderr, "ERR : UNDEFINED\n");
		return (true);
	}	
	else if (errnumb == ERR_UNKNOWN)
	{
		fprintf(stderr, "ERR : UKNOWN\n");
		return (true);
	}
	else if (errnumb == ERR_QUOTATION)
	{
		fprintf(stderr, "ERR : QUOTATION\n");
		return (true);
	}
	else if (errnumb == ERR_INVALIDCHR)
	{
		fprintf(stderr, "ERR : INVALIDCHR\n");
		return (true);
	}
	else if (errnumb == ERR_COMMAND_404)
	{
		fprintf(stderr, "ERR : Command not found\n");
		return (true);
	}
	else if (errnumb == ERR_FINALPIPE)
	{
		fprintf(stderr, "ERR : FINAL PIPE\n");
		return (true);
	}
	else if (errnumb == ERR_REDDIR)
	{
		fprintf(stderr, "ERR : REDDIRECTION ERROR\n");
		return (true);
	}
	return (false);
}
