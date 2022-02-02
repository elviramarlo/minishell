/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:50:38 by elvmarti          #+#    #+#             */
/*   Updated: 2020/10/16 10:55:48 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*pt;
	size_t	i;

	pt = (void *)malloc(num * size);
	if (!pt)
		return (NULL);
	i = 0;
	while (i <= num * size)
	{
		((char *)pt)[i] = 0;
		i++;
	}
	return (pt);
}
