/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 21:06:02 by elvmarti          #+#    #+#             */
/*   Updated: 2021/05/11 00:56:29 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *lit, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (lit[0] == '\0')
	{
		return (big);
	}
	while (j < len)
	{
		while (big[j + i] == lit[i] && (j + i) < len)
		{
			i++;
			if (lit[i] == '\0')
			{
				return (&big[j]);
			}
		}
		i = 0;
		j++;
	}
	return ((char *) '\0');
}
