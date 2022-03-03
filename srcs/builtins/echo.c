/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:02:19 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/03 19:43:37 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(t_shell *shell, int *y)
{
	int	x;
	int	flag;

	flag = 0;
	while (shell->cmd[*y] != 0 && !ft_strncmp(shell->cmd[*y], "-n", 2))
	{
		x = 1;
		while (shell->cmd[*y][x] == 'n')
			x++;
		if (shell->cmd[*y][x] == '\0')
		{
			flag = 1;
			*y += 1;
		}
		else
			break ;
	}
	return (flag);
}

void	ft_echo(t_shell *shell)
{
	int	y;
	int	flag;

	y = 1;
	flag = check_flag(shell, &y);
	while (shell->cmd[y])
	{
		printf("%s", shell->cmd[y]);
		if (shell->cmd[y + 1])
			printf(" ");
		y++;
	}
	if (flag == 0)
		printf("\n");
	shell->isbuiltin = 1;
}
