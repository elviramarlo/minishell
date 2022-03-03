/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/03 20:21:50 by elvmarti         ###   ########.fr       */
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

void	handle_command(t_shell *shell)
{
	char	**restored_env_var;
	int fd = 0;

	restored_env_var = restore_env_var_for_command(shell);
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
	{
		if (is_redirection(shell, '>') || is_redirection(shell, '<'))
			handle_redirection(shell, fd);
		check_is_builtin(shell);
		if (shell->isbuiltin && fd)
			dup2(STDOUT_FILENO, fd);
		else if (!shell->isbuiltin)
			execve(shell->currently_running_cmd_path, shell->cmd, restored_env_var);
	}
	else
	{
		wait(&shell->last_process_result);
		if (fd)
			close(fd);
		kill(shell->running_process_pid, SIGINT);
		free_array(restored_env_var);
	}
}
