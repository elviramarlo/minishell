/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:52 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/05 16:34:55 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* char	**create_array_only_cmd2(t_shell *shell, char c)
{
	char **new_array_cmd;
	int	len;
	int	i;

	len = 1;
	while (ft_strcmp(shell->cmd[len], ">"))
		len++;
	len++;
	i = 0;
	while (shell->cmd[len])
	{
		len++;
		i++;
	}
	new_array_cmd = malloc(sizeof(char *) * (i + 1));
	len = 0;
	while (shell->cmd[len][0] == c)
		len++;
	len++;
	i = 0;
	while (shell->cmd[len])
	{
		new_array_cmd[i] = ft_strdup(shell->cmd[len]);
		len++;
		i++;
	}
	new_array_cmd[i] = NULL;
	return (new_array_cmd);
}
 */

char	**create_array_only_cmd(t_shell *shell, char c, char c2)
{
	char **new_array_cmd;
	int	len;
	int	i;

	len = 0;
	while (shell->cmd[len])
	{
		if (shell->cmd[len + 1][0] == c || shell->cmd[len + 1][0] == c2)
			break ;
		len++;
	}
	new_array_cmd = malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i <= len)
	{
		new_array_cmd[i] = ft_strdup(shell->cmd[i]);
		i++;
	}
	new_array_cmd[i] = NULL;
	return (new_array_cmd);
}

char	*join_array(char **array, int start, char restorable_divider)
{
	int		i;
	char	*ret;
	char	*temp;

	i = start;
	ret = array[i++];
	while (array[i])
	{
		temp = ret;
		if (restorable_divider)
		{
			ret = malloc(ft_strlen(temp) + 2);
			ft_strlcpy(ret, temp, ft_strlen(temp) + 1);
			ret[ft_strlen(temp)] = restorable_divider;
			free(temp);
			temp = ret;
		}
		ret = ft_strjoin(temp, array[i]);
		free(array[i]);
		free(temp);
		i++;
	}
	return (ret);
}

void	free_matrix(char ***array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i][0]),
		free(array[i][1]);
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
