/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:05:20 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/17 19:39:31 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	num_quotes(t_shell *shell, t_aux_parse *parse)
{
	int i;

	i = 0;
	while (shell->prompt[i])
	{
		if (shell->prompt[i] == '"')
			parse->num_quotes++;
		i++;
	}
	if (parse->num_quotes % 2 != 0)
	{
		printf("Comillas impares\n");
		exit (-1);
	}
}

static void	quotes(t_shell *shell, t_aux_parse *parse, char **cmd)
{
	int	start;
	int len = 0;

	parse->i++;
	start = parse->i;
	while (shell->prompt[parse->i] != '"' && shell->prompt[parse->i] != '\0')
	{
		parse->i++;
		len++;
	}
	cmd[parse->x] = ft_substr(shell->prompt, start, len);
	parse->x++;
	parse->i++;
}

static void	no_quotes(t_shell *shell, t_aux_parse *parse, char **cmd)
{
	int start;
	int len = 0;
	 
	start = parse->i;
	while (shell->prompt[parse->i] != ' ' && shell->prompt[parse->i] != '"'
		&& shell->prompt[parse->i] != '\0')
	{
		parse->i++;
		len++;
	}
	cmd[parse->x] = ft_substr(shell->prompt, start, len);
	parse->x++;
}

static int	num_str(char *prompt, char c)
{
	int	i;
	int	num_str;
	int	quote;

	i = 0;
	quote =  0;
	num_str = 1;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '"' && !quote)
		{
			quote =  1;
			num_str++;
			i++;
		}
		if (quote && prompt[i] == '"')
			quote = 0;
		if (prompt[i - 1] == c && prompt[i] != c && !quote)
			num_str++;
		i++;
	}
	return (num_str);
}

char	**parse_prompt(t_shell *shell)
{
	char		**cmd;
	int			n_str;
	t_aux_parse	parse;

	ft_bzero(&parse, sizeof(t_aux_parse));
	n_str = num_str(shell->prompt, ' ');
	cmd = (char **)malloc(sizeof(char*) * (n_str + 1));
	num_quotes(shell, &parse);
	while (shell->prompt[parse.i] != '\0')
	{
		if (shell->prompt[parse.i] != '"' && shell->prompt[parse.i] != ' ')
			no_quotes(shell, &parse, cmd);
		else if (shell->prompt[parse.i] == '"')
			quotes(shell, &parse, cmd);
		else if (shell->prompt[parse.i] == ' ')
			parse.i++;
	}
	cmd[parse.x] = 0;
	parse.i = 0;
	parse.x = 0;
	return (cmd);
}
