/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/25 17:36:46 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command(t_shell *shell)
{
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
		execv(shell->currently_running_cmd_path, shell->cmd);
	else
	{
		wait(&shell->last_process_result);
		printf("PID exit: %d\n", shell->last_process_result);
	}
}
