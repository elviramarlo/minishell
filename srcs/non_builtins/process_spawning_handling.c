/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/26 15:41:54 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**restore_path_for_command(t_shell *shell)
{
	char	**restored_path;
	char	*temp;
	int		i;

	i = 0;
	while (shell->env_variables[i])
		i++;
	restored_path = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (shell->env_variables[i])
	{
		temp = ft_strjoin(shell->env_variables[i][0], "=");
		restored_path[i] = ft_strjoin(temp, shell->env_variables[i][1]);
		free(temp);
		i++;
	}
	restored_path[i] = 0;
	return (restored_path);
}

void	handle_command(t_shell *shell)
{
	char	**restored_path;
	int		i;

	i = 0;
	restored_path = restore_path_for_command(shell);
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
		execve(shell->currently_running_cmd_path, shell->cmd, restored_path);
	else
	{
		wait(&shell->last_process_result);
		kill(shell->running_process_pid, SIGINT);
		while (restored_path[i])
			free(restored_path[i++]);
		free(restored_path);
	}
}
