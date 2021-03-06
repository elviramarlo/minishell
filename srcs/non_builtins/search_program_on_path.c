/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_program_on_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:30:32 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/09 16:41:32 by elvmarti         ###   ########.fr       */
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
			return (shell->env_variables[i]);
		i++;
	}
	return (NULL);
}

static char	*handle_full_path_in_command(t_shell *shell)
{
	struct stat	*stat_result;
	char		*path;
	char		*home_path;

	home_path = find_env_variable("HOME", shell)[1];
	stat_result = malloc(sizeof(struct stat));
	if (ft_strnstr(shell->cmd[0], "~/", 2))
		path = ft_strjoin(home_path, &shell->cmd[pos_cmd(shell)][1]);
	else
		path = ft_strdup(shell->cmd[0]);
	stat(path, stat_result);
	if (access(path, X_OK) != -1
		&& ((stat_result->st_mode) & S_IFMT) == S_IFREG)
	{
		free(stat_result);
		return (path);
	}
	free(path);
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
	stat_result = malloc(sizeof(struct stat));
	while (split_path[i])
	{
		temp = ft_strjoin(split_path[i], "/");
		full_exec_path = ft_strjoin(temp, shell->cmd[pos_cmd(shell)]);
		stat(full_exec_path, stat_result);
		if (access(full_exec_path, X_OK) != -1
			&& ((stat_result->st_mode) & S_IFMT) == S_IFREG)
		{
			free(stat_result);
			free(temp);
			return (full_exec_path);
		}
		free(full_exec_path);
		free(temp);
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
	int		i;

	i = 0;
	if (shell->isvoid)
		return (NULL);
	if (ft_strchr(shell->cmd[0], '/'))
		return (handle_full_path_in_command(shell));
	path_val = find_env_variable("PATH", shell);
	if (!path_val)
		return (NULL);
	split_path = ft_split(path_val[1], ':');
	expanded_path = get_file_path_expanded(shell, split_path);
	while (split_path[i])
		free(split_path[i++]);
	free(split_path);
	return (expanded_path);
}
