/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:52 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/24 16:38:21 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_array(char **array, int start)
{
	int		i;
	char	*ret;
	char	*temp;

	i = start;
	ret = array[i++];
	while (array[i])
	{
		temp = ret;
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
