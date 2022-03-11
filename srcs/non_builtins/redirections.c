/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:59:28 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/11 16:53:48 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**handle_redir_output(t_shell *shell, int parent_cmd)
{
	int	fd;

	fd = 0;
	if (shell->redir)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	else if (shell->redir_doble)
		fd = open(shell->file_redirection, O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (!parent_cmd)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	free(shell->file_redirection);
	if (shell->cmd[0][0] != '>')
		return (create_array_only_cmd(shell, '>', '<'));
	else
		return (&shell->cmd[pos_cmd(shell)]);
}

static char	**handle_heredoc(t_shell *shell)
{
	int		heredoc_fds[2];
	char	*line;
	char	*temp;
	char	*hd_keyword;
	char	**new_cmd;

	new_cmd = create_array_only_cmd(shell, '<', '>');
	hd_keyword = shell->file_redirection;
	pipe(heredoc_fds);
	line = readline("> ");
	while (line && !ft_strnstr(line, hd_keyword, ft_strlen(line)))
	{
		temp = replace_dollar_variable_in_string(line, shell);
		free(line);
		write(heredoc_fds[1], temp, ft_strlen(temp));
		write(heredoc_fds[1], "\n", 1);
		free(temp);
		line = readline("> ");
	}
	free(line);
	dup2(heredoc_fds[0], STDIN_FILENO);
	close(heredoc_fds[0]);
	close(heredoc_fds[1]);
	return (new_cmd);
}

char	**handle_redir_input(t_shell *shell, int parent_cmd)
{
	int		fd;

	fd = 0;
	if (shell->redir)
	{
		fd = open(shell->file_redirection, O_RDONLY);
		if (fd < 0)
		{
			shell->redir_failed = 1;
			ft_error(ft_strdup(strerror(errno)), errno, shell);
			close(fd);
			free(shell->file_redirection);
		}
		else
		{
			if (!parent_cmd)
				dup2(fd, STDIN_FILENO);
			close(fd);
			free(shell->file_redirection);
			return (create_array_only_cmd(shell, '<', '>'));
		}
	}
	else
		return (handle_heredoc(shell));
	return (NULL);
}

char	**handle_redirection(t_shell *shell, int parent_cmd)
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
		cmd = handle_redir_aux(shell, &i, cmd, parent_cmd);
		i++;
	}
	if (shell->redir || shell->redir_doble)
		return (cmd);
	else
		return (NULL);
}
