/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:52 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/23 21:00:32 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free(temp);
		i++;
	}
	return (ret);
}

void	free_array(char ***array)
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
