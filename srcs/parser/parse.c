/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:05:20 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/26 17:11:07 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	make_str(char *prompt, t_aux_parse *parse, char **cmd)
{
	if (parse->check && cmd[parse->x - 1])
	{
		parse->x--;
		cmd[parse->x] = ft_strjoin(cmd[parse->x],
				ft_substr(prompt, parse->start, parse->len));
		parse->check = 0;
	}
	else
		cmd[parse->x] = ft_substr(prompt, parse->start, parse->len);
	parse->x++;
	parse->len = 0;
}

static void	quotes(char *prompt, t_aux_parse *parse, char **cmd, char q)
{
	if (prompt[parse->i - 1] != C_SP && parse->i)
		parse->check = 1;
	while (prompt[parse->i] == q)
		parse->i++;
	parse->start = parse->i;
	while (prompt[parse->i] != q && prompt[parse->i])
	{
		parse->i++;
		parse->len++;
	}
	if (parse->len > 0)
		make_str(prompt, parse, cmd);
	parse->i++;
}

static void	no_quotes(char *prompt, t_aux_parse *parse, char **cmd)
{
	if (prompt[parse->i - 1] == C_DQ || prompt[parse->i - 1] == C_SQ)
		parse->check = 1;
	parse->start = parse->i;
	while (prompt[parse->i] != C_SP && prompt[parse->i] != C_DQ
		&& prompt[parse->i] != C_SQ && prompt[parse->i])
	{
		parse->i++;
		parse->len++;
	}
	make_str(prompt, parse, cmd);
}

char	**parse_prompt(t_shell *shell, char *prompt)
{
	char		**cmd;
	t_aux_parse	parse;

	ft_bzero(&parse, sizeof(t_aux_parse));
	cmd = malloc(sizeof(char *) * (num_str(shell->prompt, &parse) + 1));
	parse.i = 0;
	shell->isvoid = 0;
	while (prompt[parse.i])
	{
		if (prompt[parse.i] == C_DQ)
			quotes(prompt, &parse, cmd, C_DQ);
		else if (prompt[parse.i] == C_SQ)
			quotes(prompt, &parse, cmd, C_SQ);
		else if (prompt[parse.i] == C_SP)
			parse.i++;
		else
			no_quotes(prompt, &parse, cmd);
	}
	cmd[parse.x] = 0;
	parse.i = 0;
	parse.x = 0;
	if (!cmd || cmd[0] == 0)
		shell->isvoid = 1;
	return (cmd);
}
