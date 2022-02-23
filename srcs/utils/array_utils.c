/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:52 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/21 19:45:51 by gaguado-         ###   ########.fr       */
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
