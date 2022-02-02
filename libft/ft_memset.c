/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:58:49 by elvmarti          #+#    #+#             */
/*   Updated: 2020/10/06 13:19:58 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		((unsigned char*)ptr)[i] = x;
		i++;
	}
	return (ptr);
}
