/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:59:28 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/03 20:17:40 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redir_output(t_shell *shell, int fd)
{
	if (shell->redir)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_TRUNC);
	else if (shell->redir_doble)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	shell->cmd = create_array_only_cmd(shell, '>');
}

void	handle_redirection(t_shell *shell, int fd)
{
	if (is_redirection(shell, '>'))
		handle_redir_output(shell, fd);
	else if (is_redirection(shell, '<'))
	{
		fd = open(shell->file_redirection, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		shell->cmd = create_array_only_cmd(shell, '<');
	}
	
	shell->redir_doble = 0;
	shell->redir = 0;
}

int	is_redirection(t_shell *shell, char c)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (ft_strchr(shell->cmd[i], c) && ft_strchr(shell->cmd[i + 1], c))
		{
			shell->redir_doble = 1;
			shell->file_redirection = ft_strdup(shell->cmd[i + 2]);
			return (1);
		}
		else if (ft_strchr(shell->cmd[i], c))
		{
			shell->redir = 1;
			shell->file_redirection = ft_strdup(shell->cmd[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}
