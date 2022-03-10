/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:40:36 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/08 20:06:26 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, char **cmd)
{
	int	num;

	if (!cmd[1])
		exit (0);
	else if (ft_isdigit_str(cmd[1]) && cmd[2])
	{
		num = ft_atoi(cmd[1]);
		if (ft_atoi(cmd[1]) > 255)
			num = num % 256;
		while (num < 0)
			num = num + 256;
		exit(num);
	}
	if (!ft_isdigit_str(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_error(ft_strjoin(cmd[1], ": numeric argument required"),
			255, shell);
		exit (255);
	}
	else
		ft_error(ft_strdup("minishell: exit: too many arguments"), 1, shell);
	shell->isbuiltin = 1;
}
