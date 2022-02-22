/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:52 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/22 20:16:10 by gaguado-         ###   ########.fr       */
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
			ret = malloc(strlen(temp) + 1);
			ft_strlcpy(ret, temp, ft_strlen(temp) + 1);
			ret[ft_strlen(temp) + 1] = restorable_divider;
			free(temp);
			temp = ret;
		}
		ret = ft_strjoin(temp, array[i]);
		free(temp);
		i++;
	}
	return (ret);
}
