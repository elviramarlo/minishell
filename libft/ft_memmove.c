/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:58:30 by elvmarti          #+#    #+#             */
/*   Updated: 2020/10/08 13:34:28 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*pt1;
	char	*pt2;
	size_t	i;

	pt1 = (char *)s1;
	pt2 = (char *)s2;
	i = -1;
	if (pt1 == pt2)
		return (pt1);
	if (pt2 < pt1)
	{
		while (n > 0)
		{
			pt1[n - 1] = pt2[n - 1];
			n--;
		}
	}
	else
	{
		while (++i < n)
			pt1[i] = pt2[i];
	}
	return (pt1);
}
