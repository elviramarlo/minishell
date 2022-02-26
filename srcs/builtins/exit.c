/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:40:36 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/25 17:29:26 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	if (!shell->cmd[1] || (ft_isdigit_str(shell->cmd[1]) && !shell->cmd[2]))
		exit (0);
	else if (!ft_isdigit_str(shell->cmd[1]) && !shell->cmd[2])
	{
		printf(RED"exit: %s: numeric argument required\n"RESET, shell->cmd[1]);
		exit (-1);
	}
	else
		printf(RED"exit: too many arguments\n"RESET);
}
