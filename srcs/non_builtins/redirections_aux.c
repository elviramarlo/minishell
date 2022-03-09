/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:31:29 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/09 17:27:35 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_redir(char *cmd, t_shell *shell)
{
	if (!cmd)
	{
		ft_error(ft_strdup("Syntax error near unexpected token 'newline'"), 258,
			shell);
		exit(258);
	}
	if (ft_strchr("|<>", cmd[0]))
	{
		ft_error(ft_strdup("Syntax error near unexpected token"), 258,
			shell);
		exit(258);
	}
}

static void	get_file_name(t_shell *shell, int *i, int doble_redir)
{
	if (doble_redir)
	{
		if (*i >= 1)
			parse_redir(shell->cmd[*i + 2], shell);
		shell->redir_doble = 1;
		shell->file_redirection = ft_strdup(shell->cmd[*i + 2]);
	}
	else if (!doble_redir)
	{
		if (*i > 0)
			parse_redir(shell->cmd[*i + 1], shell);
		shell->redir = 1;
		shell->file_redirection = ft_strdup(shell->cmd[*i + 1]);
	}
}

char	**handle_redir_aux(t_shell *shell, int *i, char **cmd, int fd)
{
	if (ft_strchr(shell->cmd[*i], '>') && ft_strchr(shell->cmd[*i + 1], '>'))
	{
		get_file_name(shell, i, 1);
		cmd = handle_redir_output(shell, fd);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '>'))
	{
		get_file_name(shell, i, 0);
		cmd = handle_redir_output(shell, fd);
	}
	if (ft_strchr(shell->cmd[*i], '<') && ft_strchr(shell->cmd[*i + 1], '<'))
	{
		get_file_name(shell, i, 1);
		cmd = handle_redir_input(shell, fd);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '<'))
	{
		get_file_name(shell, i, 0);
		cmd = handle_redir_input(shell, fd);
	}
	return (cmd);
}

int	pos_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if ((shell->cmd[0][0] == '>' && shell->cmd[1][0] == '>')
		|| (shell->cmd[0][0] == '<' && shell->cmd[1][0] == '<'))
		return (3);
	else if (shell->cmd[0][0] == '>' || shell->cmd[0][0] == '<')
		return (2);
	else
		return (0);
}
