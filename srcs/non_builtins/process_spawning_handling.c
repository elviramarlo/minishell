/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/10 18:00:07 by elvmarti         ###   ########.fr       */
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

void	handle_command(t_shell *shell, int ifd, int ofd, int is_not_last)
{
	char	**restored_env_var;
	char	**new_cmd;

	restored_env_var = restore_env_var_for_command(shell);
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
	{
		dup2(shell->fd_backup, STDIN_FILENO);
		if (is_not_last)
			dup2(ifd, STDOUT_FILENO);
		close(ofd);
		new_cmd = handle_redirection(shell, 0);
		if (!new_cmd)
			new_cmd = shell->cmd;
		shell->currently_running_cmd_path = search_program_on_path(shell);
		check_is_builtin(shell);
		if (!shell->isbuiltin && !shell->redir_failed)
			execve(shell->currently_running_cmd_path, new_cmd,
				restored_env_var);
		exit (shell->last_process_result);
	}
	waitpid(shell->running_process_pid, &shell->last_process_result, 0);
	shell->last_process_result = WEXITSTATUS(shell->last_process_result);
	free_array(restored_env_var);
}
