/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:02:19 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/10 18:23:58 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char **cmd, int *y)
{
	int	x;
	int	flag;

	flag = 0;
	while (cmd[*y] != 0 && !ft_strncmp(cmd[*y], "-n", 2))
	{
		x = 1;
		while (cmd[*y][x] == 'n')
			x++;
		if (cmd[*y][x] == '\0')
		{
			flag = 1;
			*y += 1;
		}
		else
			break ;
	}
	return (flag);
}

void	ft_echo(t_shell *shell, char **cmd)
{
	int	y;
	int	flag;

	y = 1;
	flag = check_flag(cmd, &y);
	while (cmd[y] && cmd[y][0] != '>' && cmd[y][0] != '<')
	{
		printf("%s", cmd[y]);
		if (cmd[y + 1])
			printf(" ");
		y++;
	}
	if (flag == 0)
		printf("\n");
	shell->isbuiltin = 1;
	shell->last_process_result = 0;
}
