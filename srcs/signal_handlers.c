/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:58:35 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/26 17:09:48 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	signal(sig, sigint_handler);
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\n");
	printf(CYAN"minishell> "RESET);
}
