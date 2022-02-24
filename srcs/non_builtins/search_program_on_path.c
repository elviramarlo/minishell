/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_program_on_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:30:32 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/23 18:42:33 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**find_env_variable(char *name, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env_variables[i])
	{
		if (ft_strcmp(shell->env_variables[i][0], name))
			return (&shell->env_variables[i][0]);
		i++;
	}
	return (NULL);
}

static char	*handle_full_path_in_command(t_shell *shell)
{
	struct stat	*stat_result;

	stat_result = malloc(sizeof(struct stat *));
	stat(shell->cmd[0], stat_result);
	if (access(shell->cmd[0], X_OK) != -1
		&& ((stat_result->st_mode) & S_IFMT) == S_IFREG)
	{
		free(stat_result);
		return (ft_strdup(shell->cmd[0]));
	}
	free(stat_result);
	return (NULL);
}

static char	*get_file_path_expanded(t_shell *shell, char **split_path)
{
	struct stat	*stat_result;
	char		*full_exec_path;
	char		*temp;
	int			i;

	i = 0;
	stat_result = malloc(sizeof(struct stat *));
	while (split_path[i])
	{
		temp = ft_strjoin(split_path[i], "/");
		full_exec_path = ft_strjoin(temp, shell->cmd[0]);
		stat(full_exec_path, stat_result);
		if (access(full_exec_path, X_OK) != -1
			&& ((stat_result->st_mode) & S_IFMT) == S_IFREG)
		{
			free(stat_result);
			return (full_exec_path);
		}
		free(full_exec_path);
		i++;
	}
	free(stat_result);
	return (NULL);
}

char	*search_program_on_path(t_shell *shell)
{
	char	**path_val;
	char	**split_path;
	char	*expanded_path;

	if (shell->isvoid)
		return (NULL);
	if (ft_strchr(shell->cmd[0], '/'))
		return (handle_full_path_in_command(shell));
	path_val = find_env_variable("PATH", shell);
	if (!path_val)
		return (NULL);
	split_path = ft_split(path_val[1], ':');
	expanded_path = get_file_path_expanded(shell, split_path);
	free(split_path);
	return (expanded_path);
}
