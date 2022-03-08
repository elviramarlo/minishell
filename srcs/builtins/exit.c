/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:40:36 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/08 16:36:06 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	int	num;

	if (!shell->cmd[1])
		exit (0);
	else if (ft_isdigit_str(shell->cmd[1]) && !shell->cmd[2])
	{
		num = ft_atoi(shell->cmd[1]);
		if (ft_atoi(shell->cmd[1]) > 255)
			num = num % 256;
		while (num < 0)
			num = num + 256;
		exit(num);
	}
	if (!ft_isdigit_str(shell->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_error(ft_strjoin(shell->cmd[1], ": numeric argument required"),
			255, shell);
		exit (255);
	}
	else
		ft_error(ft_strdup("minishell: exit: too many arguments"), 1, shell);
	shell->isbuiltin = 1;
}
