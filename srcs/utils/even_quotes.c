/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:58:01 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/28 16:58:31 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	even_quotes(t_shell *shell)
{
	int	i;
	int	dquotes;
	int	squotes;

	i = 0;
	dquotes = 0;
	squotes = 0;
	while (shell->prompt[i])
	{
		if (shell->prompt[i] == C_DQ)
			dquotes++;
		if (shell->prompt[i] == C_SQ)
			squotes++;
		i++;
	}
	if (dquotes % 2 != 0 || squotes % 2 != 0)
	{
		shell->isbuiltin = 1;
		return (0);
	}
	return (1);
}
