/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:06:22 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/28 16:45:30 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env_variables[i])
	{
		printf("%s=%s\n", shell->env_variables[i][0],
			shell->env_variables[i][1]);
		i++;
	}
	shell->isbuiltin = 1;
}
