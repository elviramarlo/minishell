/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:31:29 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/05 16:51:53 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_redir(char *cmd, char *cmd2)
{
	if (!cmd)
	{
		printf(RED"Syntax error near unexpected token 'newline'\n"RESET);
		exit(-1);
	}
	if (ft_strchr("|<>", cmd[0]) || ft_strchr("<>", cmd2[0]))
	{
		printf(RED"Syntax error near unexpected token\n"RESET);
		exit(-1);
	}
}

static void	get_file_name(t_shell *shell, int *i, int doble_redir)
{
	if (doble_redir)
	{
		if (*i > 1)
			parse_redir(shell->cmd[*i + 2], shell->cmd[*i - 2]);
		shell->redir_doble = 1;
		shell->file_redirection = ft_strdup(shell->cmd[*i + 2]);
	}
	else if (!doble_redir)
	{
		if (*i > 0)
			parse_redir(shell->cmd[*i + 1], shell->cmd[*i - 1]);
		shell->redir = 1;
		shell->file_redirection = ft_strdup(shell->cmd[*i + 1]);
	}
}

char	**handle_redir_aux(t_shell *shell, int *i, char **cmd)
{
	if (ft_strchr(shell->cmd[*i], '>') && ft_strchr(shell->cmd[*i + 1], '>'))
	{
		get_file_name(shell, i, 1);
		cmd = handle_redir_output(shell);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '>'))
	{
		get_file_name(shell, i, 0);
		cmd = handle_redir_output(shell);
	}
	if (ft_strchr(shell->cmd[*i], '<') && ft_strchr(shell->cmd[*i + 1], '<'))
	{
		get_file_name(shell, i, 1);
		cmd = handle_redir_input(shell);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '<'))
	{
		get_file_name(shell, i, 0);
		cmd = handle_redir_input(shell);
	}
	return (cmd);
}
