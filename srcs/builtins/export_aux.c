/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:43:58 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/10 18:46:57 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_len(char **cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd[len])
	{
		if (!ft_strchr(cmd[len], C_EQ) && len > 0)
			i++;
		len++;
	}
	return (len - i);
}
