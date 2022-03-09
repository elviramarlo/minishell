/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/09 14:25:19 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	handle_child_pipes(int input_fd, int output_fd, int pipe)
{
	if (pipe == 1 || pipe == 0)
		dup2(input_fd, STDOUT_FILENO);
	if (pipe == 0 || pipe == -1)
		dup2(output_fd, STDIN_FILENO);
	close(input_fd);
	close(output_fd);
}

static void	remove_heredoc_markers(t_shell *shell)
{
	int		i;
	char	**temp;

	i = 0;
	while (shell->cmd[i])
		i++;
	temp = malloc(sizeof(char *) * 1 + 1);
	temp[0] = ft_strdup(shell->cmd[0]);
	free_array(shell->cmd);
	shell->cmd = temp;
}

void	handle_heredoc(t_shell *shell)
{
	int		heredoc_fds[2];
	char	*line;
	char	*temp;

	pipe(heredoc_fds);
	remove_heredoc_markers(shell);
	line = readline("> ");
	while (line && !ft_strnstr(line, "EOF", ft_strlen("EOF")))
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
}

void	handle_command(t_shell *shell, int input_fd, int output_fd, int pipe)
{
	char	**restored_env_var;
	char	**new_cmd;
	int		running_process_pid;

	restored_env_var = restore_env_var_for_command(shell);
	running_process_pid = fork();
	if (pipe == -1)
		shell->running_process_pid = running_process_pid;
	if (running_process_pid == 0)
	{
		handle_child_pipes(input_fd, output_fd, pipe);
		handle_heredoc(shell);
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
	if (running_process_pid != shell->running_process_pid)
		waitpid(running_process_pid, NULL, 0);
	free_array(restored_env_var);
}
