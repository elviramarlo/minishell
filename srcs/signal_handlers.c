/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:58:35 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/10 16:29:54 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_handler(int sig)
{
	signal(sig, sigint_handler);
	if (!g_is_interactive)
		return ;
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\n");
	printf(CYAN"minishell> "RESET);
}

static void	sigquit_handler(int sig)
{
	char	*nbr;

	if (!g_is_interactive)
	{
		nbr = ft_itoa(sig);
		ft_putstr_fd("\nQuit: ", 2);
		ft_putendl_fd(nbr, 2);
		free(nbr);
		return ;
	}
	signal(sig, sigquit_handler);
}

void	add_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
