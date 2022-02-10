/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:08:52 by elvmarti          #+#    #+#             */
/*   Updated: 2021/10/29 18:00:49 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	is_error(long long int signo, long long int sol)
{
	if (sol * signo > 2147483648)
	{
		printf("Error\n");
		exit(1);
	}
	else if (sol * signo < -2147483648)
	{
		printf("Error\n");
		exit(1);
	}
}

int	ft_atoi(char *str)
{
	long long int	signo;
	long long int	sol;

	signo = 1;
	sol = 0;
	while (*str == ' ' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signo = -signo;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		is_error(signo, sol);
		sol = sol * 10 + (*str - 48);
		str++;
	}
	return (signo * sol);
}
