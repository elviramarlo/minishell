/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/01 16:58:24 by elvmarti         ###   ########.fr       */
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
	int		i;

	i = 0;
	restored_env_var = restore_env_var_for_command(shell);
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
		execve(shell->currently_running_cmd_path, shell->cmd, restored_env_var);
	else
	{
		wait(&shell->last_process_result);
		kill(shell->running_process_pid, SIGINT);
		while (restored_env_var[i])
			free(restored_env_var[i++]);
		free(restored_env_var);
	}
}
