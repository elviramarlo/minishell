/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:59:28 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/04 23:05:52 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**handle_redir_output(t_shell *shell, int fd)
{
	if (shell->redir)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_TRUNC);
	else if (shell->redir_doble)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (create_array_only_cmd(shell, '>'));
}

char	**handle_redirection(t_shell *shell, int fd)
{
	shell->redir_failed = 0;
	if (is_redirection(shell, '>'))
		return (handle_redir_output(shell, fd));
	else if (is_redirection(shell, '<'))
	{
		fd = open(shell->file_redirection, O_RDONLY);
		if (fd < 0)
		{
			printf(RED"No such file or directory\n"RESET);
			shell->redir_failed = 1;
		}
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (create_array_only_cmd(shell, '<'));
		}
	}
	shell->redir_doble = 0;
	shell->redir = 0;
	return (NULL);
}

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

int	is_redirection(t_shell *shell, char c)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (ft_strchr(shell->cmd[i], c) && ft_strchr(shell->cmd[i + 1], c))
		{
			if (i > 1)
				parse_redir(shell->cmd[i + 2], shell->cmd[i - 2]);
			shell->redir_doble = 1;
			shell->file_redirection = ft_strdup(shell->cmd[i + 2]);
			return (1);
		}
		else if (ft_strchr(shell->cmd[i], c))
		{
			if (i > 0)
				parse_redir(shell->cmd[i + 1], shell->cmd[i - 1]);
			shell->redir = 1;
			shell->file_redirection = ft_strdup(shell->cmd[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}
