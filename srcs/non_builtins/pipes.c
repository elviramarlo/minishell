/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:28:55 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/08 22:30:09 by gaguado-         ###   ########.fr       */
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

static void	process_command(t_shell *shell, int pc, int *pipe_fds, int i)
{
	shell->currently_running_cmd_path = search_program_on_path(shell);
	if (shell->currently_running_cmd_path || shell->cmd[0][0] == '>')
	{
		if (pc == 1 || i == pc - 1)
			handle_command(shell, pipe_fds[1], pipe_fds[0], -1);
		else if (i == 0)
			handle_command(shell, pipe_fds[1], pipe_fds[0], 1);
		else
			handle_command(shell, pipe_fds[1], pipe_fds[0], 0);
		if (pc == 1 || i == pc - 1)
			close(pipe_fds[1]);
		free(shell->currently_running_cmd_path);
	}
	else
		printf("minishell: command not found: %s\n", shell->cmd[0]);
}

void	handle_pipes_and_command(t_shell *shell)
{
	int		i;
	int		pipe_fds[2];
	int		pipe_count;

	i = 0;
	pipe_count = count_pipes(shell->cmd_backlog) + 1;
	if (pipe_count != 1 && pipe_count != i + 1)
		pipe(pipe_fds);
	while (i < pipe_count)
	{
		handle_pipe(i, shell);
		if (!shell->isvoid)
		{
			if (ft_strcmp(shell->cmd[0], "exit"))
				check_is_builtin(shell);
			if (!shell->isbuiltin)
				process_command(shell, pipe_count, pipe_fds, i);
		}
		i++;
	}
	waitpid(shell->running_process_pid, &shell->last_process_result, 0);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
}
