/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:44:02 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/25 17:25:17 by elvmarti         ###   ########.fr       */
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
		if (shell->prompt[i] == DQT)
			dquotes++;
		if (shell->prompt[i] == SQT)
			squotes++;
		i++;
	}
	if (dquotes % 2 != 0 || squotes % 2 != 0)
		return (0);
	return (1);
}

static void	malloc_noquotes(char *prompt, t_aux_parse *p)
{
	while (prompt[p->i] != SPC && prompt[p->i])
	{
		if (prompt[p->i] == DQT || prompt[p->i] == SQT)
		{
			p->i++;
			while (prompt[p->i] != DQT && prompt[p->i] != SQT
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
	if ((prompt[p->i] == DQT && prompt[p->i - 1] == DQT)
		|| (prompt[p->i] == SQT && prompt[p->i - 1] == SQT))
		p->i++;
	else
	{
		while (prompt[p->i] != DQT && prompt[p->i] != SQT)
			p->i++;
		if (prompt[p->i + 1] == SPC || !prompt[p->i + 1])
			p->num_str++;
		else
		{
			p->i++;
			malloc_noquotes(prompt, p);
		}
		p->i++;
	}
}

int	num_str(char *prompt, t_aux_parse *p)
{
	p->num_str = 0;
	while (prompt[p->i])
	{
		if (prompt[p->i] == DQT || prompt[p->i] == SQT)
			malloc_quotes(prompt, p);
		if (prompt[p->i] != DQT && prompt[p->i] != SQT && prompt[p->i] != SPC
			&& prompt[p->i])
			malloc_noquotes(prompt, p);
		if (prompt[p->i])
			p->i++;
	}
	//printf("NUM MALLOC %d\n", p->num_str);
	return (p->num_str);
}
