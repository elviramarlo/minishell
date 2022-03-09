/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:44:02 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/09 16:25:50 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	malloc_noquotes(char *prompt, t_aux_parse *p)
{
	while (prompt[p->i] != C_SP && prompt[p->i] != C_PP && prompt[p->i] != '<'
		&& prompt[p->i] != '>' && prompt[p->i])
	{
		if (prompt[p->i] == C_DQ || prompt[p->i] == C_SQ)
		{
			p->i++;
			while (prompt[p->i] != C_DQ && prompt[p->i] != C_SQ
				&& prompt[p->i])
				p->i++;
		}
			p->i++;
	}
	p->num_str++;
}

static void	malloc_quotes(char *prompt, t_aux_parse *p)
{
	p->i++;
	if ((prompt[p->i] == C_DQ && prompt[p->i - 1] == C_DQ)
		|| (prompt[p->i] == C_SQ && prompt[p->i - 1] == C_SQ))
		p->i++;
	else
	{
		while (prompt[p->i] != C_DQ && prompt[p->i] != C_SQ)
			p->i++;
		if (prompt[p->i + 1] == C_SP || !prompt[p->i + 1])
			p->num_str++;
		else
		{
			p->i++;
			malloc_noquotes(prompt, p);
		}
		if (prompt[p->i] != C_PP && prompt[p->i] != '<' && prompt[p->i] != '>')
			p->i++;
	}
}

int	num_str(char *prompt, t_aux_parse *p)
{
	p->num_str = 0;
	while (prompt[p->i])
	{
		if (prompt[p->i] != C_DQ && prompt[p->i] != C_SQ && prompt[p->i] != C_SP
			&& prompt[p->i] && prompt[p->i] != C_PP && prompt[p->i] != '<'
			&& prompt[p->i] != '>')
			malloc_noquotes(prompt, p);
		else if (prompt[p->i] == C_DQ || prompt[p->i] == C_SQ)
			malloc_quotes(prompt, p);
		else if (prompt[p->i] == C_PP || prompt[p->i] == '<'
			|| prompt[p->i] == '>')
		{
			p->i++;
			p->num_str++;
		}
		else if (prompt[p->i])
			p->i++;
	}
	return (p->num_str);
}
