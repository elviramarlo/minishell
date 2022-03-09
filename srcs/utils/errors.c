/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:08:55 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/09 16:21:43 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *msg, int errnum, t_shell *shell)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	shell->errnum = errnum;
	shell->last_process_result = errnum;
	if (msg)
		free(msg);
}
