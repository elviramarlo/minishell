/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:31:29 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/10 18:36:58 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_redir(char *cmd, t_shell *shell, int parent_cmd)
{
	if (!cmd)
	{
		ft_error(ft_strdup(ERR), 258, shell);
		if (!parent_cmd)
			exit(258);
		else
			shell->error_redir = 1;
	}
	else if (ft_strchr("|<>", cmd[0]))
	{
		ft_error(ft_strjoin("minishell: syntax error near unexpected token: ",
				cmd), 258, shell);
		if (!parent_cmd)
			exit(258);
		else
			shell->error_redir = 1;
	}
}

static void	get_file_name(t_shell *shell, int *i, int doble_redir,
	int parent_cmd)
{
	if (doble_redir)
	{
		if (*i >= 1)
			parse_redir(shell->cmd[*i + 2], shell, parent_cmd);
		shell->redir_doble = 1;
		if (!shell->error_redir)
			shell->file_redirection = ft_strdup(shell->cmd[*i + 2]);
	}
	else if (!doble_redir)
	{
		if (*i > 0)
			parse_redir(shell->cmd[*i + 1], shell, parent_cmd);
		shell->redir = 1;
		if (!shell->error_redir)
			shell->file_redirection = ft_strdup(shell->cmd[*i + 1]);
	}
}

char	**handle_redir_aux(t_shell *shell, int *i, char **cmd, int parent_cmd)
{
	if (ft_strchr(shell->cmd[*i], '>') && ft_strchr(shell->cmd[*i + 1], '>'))
	{
		get_file_name(shell, i, 1, parent_cmd);
		cmd = handle_redir_output(shell, parent_cmd);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '>'))
	{
		get_file_name(shell, i, 0, parent_cmd);
		cmd = handle_redir_output(shell, parent_cmd);
	}
	if (ft_strchr(shell->cmd[*i], '<') && ft_strchr(shell->cmd[*i + 1], '<'))
	{
		get_file_name(shell, i, 1, parent_cmd);
		cmd = handle_redir_input(shell, parent_cmd);
		*i = *i + 1;
	}
	else if (ft_strchr(shell->cmd[*i], '<'))
	{
		get_file_name(shell, i, 0, parent_cmd);
		cmd = handle_redir_input(shell, parent_cmd);
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
