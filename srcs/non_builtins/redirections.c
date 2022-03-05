/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:59:28 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/05 17:11:07 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**handle_redir_output(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->redir)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	else if (shell->redir_doble)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_APPEND, 0600);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	//if (shell->cmd[0][0] != '>')
		return (create_array_only_cmd(shell, '>', '<'));
/* 	else
		return (create_array_only_cmd2(shell, '>')); */
}

char	**handle_redir_input(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->redir)
	{
		fd = open(shell->file_redirection, O_RDONLY);
		if (fd < 0)
		{
			printf(RED"No such file or directory\n"RESET);
			close(fd);
			shell->redir_failed = 1;
		}
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (create_array_only_cmd(shell, '<', '>'));
		}
	}
	return (NULL);
}

char	**handle_redirection(t_shell *shell)
{
	int		i;
	char	**cmd;

	cmd = NULL;
	shell->redir = 0;
	shell->redir_doble = 0;
	shell->redir_failed = 0;
	i = 0;
	while (shell->cmd[i])
	{
		cmd = handle_redir_aux(shell, &i, cmd);
		i++;
	}
	if (shell->redir || shell->redir_doble)
		return (cmd);
	else
		return (NULL);
}
