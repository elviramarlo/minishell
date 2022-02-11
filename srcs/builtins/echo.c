/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:02:19 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/11 16:45:34 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	flag(t_shell *shell, char *prompt)
{
	int	i;

	i = 4;
	shell->flag = 0;
	while (prompt[i] == ' ' || (prompt[i] == '-' && prompt[i + 1] == 'n'
			&& prompt[i + 2] == ' '))
	{
		if (ft_strnstr(prompt, "-n ", 3 + i))
		{
			shell->flag = 1;
			i += 2;
		}
		i++;
	}
	return (i);
}

void	ft_echo(t_shell *shell, char *prompt)
{
	int		i;
	char	**echo;

	i = flag(shell, prompt);
	prompt = ft_substr(prompt, i, ft_strlen(prompt));
	if (ft_strchr(prompt, '"'))
	{
		i = 0;
		echo = ft_split(prompt, '"');
		while (echo[i] != (void *)0)
		{
			printf("%s", echo[i]);
			i++;
		}
	}
	else
		printf("%s", prompt);
	if (shell->flag == 0)
		printf("\n");
}
