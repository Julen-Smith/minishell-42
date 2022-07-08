/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:23:16 by aalvarez          #+#    #+#             */
/*   Updated: 2022/07/08 18:42:54 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_interactive(int inter)
{
	unsigned int	interactive;

	interactive = 0;
	if (inter == 0 || inter == 1)
		interactive = inter;
	return (interactive);
}

void	ft_signal_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	interact_signal(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line();
		rl_redisplay();
	}
}

void	signal_handler(int signal)
{
	if (ft_interactive(-1) == 1)
		interact_signal(signal);
	else if (ft_interactive(-1) == 0)
	{
		if (signal == SIGQUIT)
		{
			ft_interactive(1);
			rl_on_new_line();
		}
		else if (signal == SIGINT)
		{
			ft_interactive(1);
			write(1, "\n", 1);
			rl_on_new_line();
		}
	}
}

void	ft_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
