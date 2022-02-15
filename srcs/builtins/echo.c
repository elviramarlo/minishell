/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:02:19 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/15 17:52:46 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_shell *shell)
{
	int i;
	int x;
	int	flag;

	i = 1;
	flag = 0;
	while (shell->cmd[i] != (void *)0 && !ft_strncmp(shell->cmd[i], "-n", 2))
	{
		x = 1;
		while (shell->cmd[i][x] == 'n')
			x++;
		if (shell->cmd[i][x] == '\0')
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	while (shell->cmd[i] != (void *)0)
	{ 
		printf("%s ", shell->cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}
