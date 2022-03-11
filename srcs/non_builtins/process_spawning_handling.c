/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawning_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:32:53 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/11 16:56:08 by gaguado-         ###   ########.fr       */
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

static int	contains_double_redir(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->cmd[++i])
		if (ft_strchr(shell->cmd[i], '<') && ft_strchr(shell->cmd[i + 1], '<'))
			return (1);
	return (0);
}

static char	**pipes_on_double_redir(t_shell *shell, int ifd, int ofd, int inl)
{
	char	**new_cmd;

	if (contains_double_redir(shell))
		new_cmd = handle_redirection(shell, 0);
	dup2(shell->fd_backup, STDIN_FILENO);
	if (inl)
		dup2(ifd, STDOUT_FILENO);
	close(ofd);
	if (!contains_double_redir(shell))
		new_cmd = handle_redirection(shell, 0);
	if (!new_cmd)
		new_cmd = shell->cmd;
	shell->currently_running_cmd_path = search_program_on_path(shell);
	return (new_cmd);
}

void	handle_command(t_shell *shell, int ifd, int ofd, int is_not_last)
{
	char	**restored_env_var;
	char	**new_cmd;

	restored_env_var = restore_env_var_for_command(shell);
	shell->running_process_pid = fork();
	if (shell->running_process_pid == 0)
	{
		new_cmd = pipes_on_double_redir(shell, ifd, ofd, is_not_last);
		check_is_builtin(shell);
		if (!shell->isbuiltin && !shell->redir_failed)
			execve(shell->currently_running_cmd_path, new_cmd,
				restored_env_var);
		exit (shell->last_process_result);
	}
	free_array(restored_env_var);
}
