/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:16:51 by elvmarti          #+#    #+#             */
/*   Updated: 2021/05/11 01:02:00 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	len_s;
	char			*str;

	if (!s)
		return (0);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	while (i < len && start < len_s)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
