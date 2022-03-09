/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:28:55 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/09 21:50:58 by gaguado-         ###   ########.fr       */
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
static char	**restore_env_var_for_command(t_shell *shell)
{
	char	**restored_env_var;
	char	*temp;
	int		i;

	i = 0;
	while (shell->env_variables[i])
		i++;
	restored_env_var = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (shell->env_variables[i])
	{
		temp = ft_strjoin(shell->env_variables[i][0], "=");
		restored_env_var[i] = ft_strjoin(temp, shell->env_variables[i][1]);
		free(temp);
		i++;
	}
	restored_env_var[i] = 0;
	return (restored_env_var);
}

void	handle_pipes_and_command(t_shell *shell)
{
	int		i;
	int		pipe_fds[2];
	char	**restored_env_var;
	char	**new_cmd;
	int		pipe_count;
	int		fdd;

	i = 0;
	fdd = STDIN_FILENO;
	pipe_count = count_pipes(shell->cmd_backlog) + 1;
	while (i < pipe_count)
	{
		handle_pipe(i, shell);
		if (!shell->isvoid)
		{
			if (ft_strcmp(shell->cmd[0], "exit"))
				check_is_builtin(shell);
			if (!shell->isbuiltin) {
				shell->currently_running_cmd_path = search_program_on_path(shell);
				if (shell->currently_running_cmd_path || shell->cmd[0][0] == '>')
				{
					restored_env_var = restore_env_var_for_command(shell);
					pipe(pipe_fds);
					shell->running_process_pid = fork();
					if (shell->running_process_pid == 0)
					{
						dup2(fdd, STDIN_FILENO);
						if (i + 1 != pipe_count)
							dup2(pipe_fds[1], STDOUT_FILENO);
						close(pipe_fds[0]);
						new_cmd = handle_redirection(shell);
						if (!new_cmd)
							new_cmd = shell->cmd;
						shell->currently_running_cmd_path = search_program_on_path(shell);
						check_is_builtin(shell);
						if (!shell->isbuiltin && !shell->redir_failed)
							execve(shell->currently_running_cmd_path, new_cmd,
								restored_env_var);
						exit (1);
					}
					waitpid(shell->running_process_pid, NULL, 0);
					close(pipe_fds[1]);
					fdd = pipe_fds[0];
					free_array(restored_env_var);
				}
				else
					printf("minishell: command not found: %s\n", shell->cmd[0]);
			}
		}
		i++;
	}
	waitpid(shell->running_process_pid, &shell->last_process_result, 0);
}
