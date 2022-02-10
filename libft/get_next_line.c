/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:14:33 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/01 23:27:12 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	read_fd(int *ret, int fd, char *buffer)
{
	*ret = read(fd, buffer, BUFFER_SIZE);
	return (*ret);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*stat[4096];
	int			ret;

	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (ret > 0 && (!(ft_strchr(stat[fd], '\n'))))
	{
		if ((read_fd(&ret, fd, buffer)) < 0)
		{
			ft_null(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		set_static(fd, stat, buffer);
	}
	ft_null(buffer);
	return (is_line(fd, line, stat, ret));
}

void	set_static(int fd, char **stat, char *buffer)
{
	char		*temp;

	if (stat[fd] == NULL)
		stat[fd] = ft_strdup(buffer);
	else
	{
		temp = stat[fd];
		stat[fd] = ft_strjoin(stat[fd], buffer);
		ft_null(temp);
	}
}

int	is_line(int fd, char **line, char **stat, int ret)
{
	char		*temp;
	int			len;

	len = 0;
	while (stat[fd][len] != '\n' && stat[fd][len] != '\0')
		len++;
	*line = ft_substr(stat[fd], 0, len);
	temp = stat[fd];
	stat[fd] = ft_substr(stat[fd], len + 1, ft_strlen(stat[fd]));
	ft_null(temp);
	if (ret == 0)
	{
		free(stat[fd]);
		stat[fd] = NULL;
		return (0);
	}
	return (1);
}

void	ft_null(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
