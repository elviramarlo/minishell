/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:28:55 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/14 17:47:13 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_pipe(int index, t_shell *shell)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	while (shell->cmd_backlog[z] && i < index)
		if (shell->cmd_backlog[z++][0] == '|')
			i++;
	i = 0;
	while (shell->cmd_backlog[i + z] && shell->cmd_backlog[i + z][0] != '|')
		i++;
	if (shell->cmd)
		free(shell->cmd);
	shell->cmd = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (shell->cmd_backlog[z] && shell->cmd_backlog[z][0] != '|')
		shell->cmd[i++] = shell->cmd_backlog[z++];
	shell->cmd[i] = 0;
}

static int	count_pipes(char **cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[i] != 0)
		if (cmd[i++][0] == '|')
			ret++;
	return (ret);
}

static void	process_command(t_shell *shell, int is_not_last)
{
	int		pipe_fds[2];

	pipe(pipe_fds);
	shell->currently_running_cmd_path = search_program_on_path(shell);
	if (shell->currently_running_cmd_path)
	{
		handle_command(shell, pipe_fds[1], pipe_fds[0], is_not_last);
		free(shell->currently_running_cmd_path);
		close(pipe_fds[1]);
		shell->fd_backup = pipe_fds[0];
	}
	else
		ft_error(ft_strjoin("minishell: command not found: ", shell->cmd[0]),
			127, shell);
}

static void	non_void_shell(t_shell *shell)
{
	char	**new_cmd;

	new_cmd = handle_redirection(shell, 1);
	if (!shell->error_redir)
		check_is_builtin(shell);
	shell->error_redir = 0;
	if (new_cmd)
		free_array(new_cmd);
}

void	handle_pipes_and_command(t_shell *shell)
{
	int		i;

	i = 0;
	shell->fd_backup = STDIN_FILENO;
	replace_home_path_on_cmd(shell);
	while (i < count_pipes(shell->cmd_backlog) + 1)
	{
		handle_pipe(i, shell);
		if (!shell->isvoid)
		{
			if (parent_process_command(shell))
				non_void_shell(shell);
			else
				process_command(shell, (i != count_pipes(shell->cmd_backlog)));
		}
		i++;

	}
	while (wait(&shell->last_process_result) > 0)
		continue ;
	if (WIFEXITED(shell->last_process_result))
		shell->last_process_result = WEXITSTATUS(shell->last_process_result);
}
