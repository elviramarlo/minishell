/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:24:34 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/14 17:46:18 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum_str(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] != c && str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	replace_home_path_on_cmd(t_shell *shell)
{
	int		i;
	char	*home_path;
	char	*path;

	i = 1;
	while (shell->cmd_backlog[i])
	{
		home_path = find_env_variable("HOME", shell)[1];
		if (ft_strnstr(shell->cmd_backlog[i], "~/", 2))
		{
			path = ft_strjoin(home_path, &shell->cmd_backlog[i][1]);
			free(shell->cmd_backlog[i]);
			shell->cmd_backlog[i] = path;
		}
		i++;
	}
}
