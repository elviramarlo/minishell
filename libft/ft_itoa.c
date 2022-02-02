/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:58:00 by elvmarti          #+#    #+#             */
/*   Updated: 2020/10/06 12:42:49 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char			*dest;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = (n < 0 ? -n : n);
	len = ft_size(nb);
	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * len + (n < 0 ? 2 : 1))))
		return (NULL);
	if (n < 0)
	{
		dest[0] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		dest[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	dest[i] = nb % 10 + '0';
	dest[len] = '\0';
	return (dest);
}
