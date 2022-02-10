/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:17:19 by elvmarti          #+#    #+#             */
/*   Updated: 2021/05/13 21:49:57 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_str(char const *s, char c)
{
	int	i;
	int	num_str;

	i = 0;
	num_str = 0;
	while (s[i] != '\0')
	{
		if ((s[i - 1] == c || i == 0) && s[i] != c)
			num_str++;
		i++;
	}
	return (num_str);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;
	int			num_str;
	size_t		start;
	size_t		end;
	int			cont;

	if (!s)
		return (NULL);
	num_str = ft_num_str(s, c);
	ptr = (char **)malloc(sizeof(char *) * num_str + 1);
	if (!ptr)
		return (NULL);
	end = 0;
	cont = -1;
	while (++cont < num_str)
	{
		start = end - 1;
		while (s[++start] == c && end < ft_strlen(s))
			end++;
		while (s[end] != c && end < ft_strlen(s))
			end++;
		ptr[cont] = ft_substr(s, start, end - start);
	}
	ptr[cont] = 0;
	return (ptr);
}
