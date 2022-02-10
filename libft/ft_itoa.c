/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:58:00 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/01 23:18:54 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

static int	isnegative(int n)
{
	if (n < 0)
		return (2);
	return (1);
}

static int	itoa_nb(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = itoa_nb(n);
	len = ft_size(nb);
	dest = (char *)malloc(sizeof(char) * len + isnegative(n));
	if (!(dest))
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
		nb /= 10;
		i--;
	}
	dest[i] = nb % 10 + '0';
	dest[len] = '\0';
	return (dest);
}
