/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 21:04:05 by elvmarti          #+#    #+#             */
/*   Updated: 2020/12/24 14:31:22 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*pt;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s[size] != '\0')
		size++;
	if (!(pt = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (pt == '\0')
		return (NULL);
	while (i < size)
	{
		pt[i] = s[i];
		i++;
	}
	pt[i] = '\0';
	return (pt);
}
