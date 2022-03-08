/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:05:20 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/06 23:54:29 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	make_str(char *prompt, t_aux_parse *parse, char **cmd)
{
	char	*tmp;
	char	*tmp_substr;

	if (parse->check && cmd[parse->x - 1])
	{
		parse->x--;
		tmp = ft_strdup(cmd[parse->x]);
		free(cmd[parse->x]);
		tmp_substr = ft_substr(prompt, parse->start, parse->len);
		cmd[parse->x] = ft_strjoin(tmp, tmp_substr);
		free(tmp);
		free(tmp_substr);
		parse->check = 0;
	}
	else
		cmd[parse->x] = ft_substr(prompt, parse->start, parse->len);
	parse->x++;
	parse->len = 0;
}

static void	quotes(char *prompt, t_aux_parse *parse, char **cmd, char q)
{
	if (parse->i && !ft_strchr(" |<>", prompt[parse->i - 1]))
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
	if (ft_strchr("|<>", prompt[parse->i]) && prompt[parse->i])
	{
		cmd[parse->x] = ft_substr(prompt, parse->i, 1);
		parse->x++;
		parse->i++;
	}
}

static void	no_quotes(char *prompt, t_aux_parse *parse, char **cmd)
{
	if (prompt[parse->i - 1] == C_DQ || prompt[parse->i - 1] == C_SQ)
		parse->check = 1;
	parse->start = parse->i;
	while (!ft_strchr(" \"'|<>", prompt[parse->i]))
	{
		parse->i++;
		parse->len++;
	}
	if (!ft_strchr(" |<>", prompt[parse->i - 1]) && parse->i)
		make_str(prompt, parse, cmd);
	if (ft_strchr("|<>", prompt[parse->i]) && prompt[parse->i])
	{
		cmd[parse->x] = ft_substr(prompt, parse->i, 1);
		parse->x++;
		parse->i++;
	}
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
		check_for_env_vars(cmd, shell, &parse);
	}
	cmd[parse.x] = 0;
	parse.i = 0;
	parse.x = 0;
	if (!cmd || cmd[0] == 0)
		shell->isvoid = 1;
	return (cmd);
}
