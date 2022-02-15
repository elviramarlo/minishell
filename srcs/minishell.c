/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/15 20:58:41 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_builtin(t_shell *shell)
{
	int i;
	int x = 0;
	int	start = 0;
	int	len = 0;

	i = 0;
	shell->cmd = malloc(456789);
	if (!ft_strchr(shell->prompt, '"') && !ft_strchr(shell->prompt, '\''))
		shell->cmd = ft_split(shell->prompt, ' ');
	else
	{
		while (shell->prompt[x] != '"')
		{
			if (shell->prompt[x] != ' ')
				len++;
			else
			{
				shell->cmd[i] = ft_substr(shell->prompt, start, len);
				start = len;
				len = 0;
			 	i++;
			}
			x++;
		}
		x++;
		while (shell->prompt[x] != '"')
		{
			len++;
			x++;
		}
		if (shell->prompt[x] == '"')
		{
			printf("%d\n", len);
			shell->cmd[i] = ft_substr(shell->prompt, start + 2, len);
			i++;
			x++;
		}
	}
	i = 0;
	while (shell->cmd[i])
	{
		printf("%s\n", shell->cmd[i]);
		i++;
	}
/* 	if (!ft_strncmp(shell->cmd[i], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(shell->cmd[i], "echo", 4))
		ft_echo(shell); */
}

int	main(int argc, char **argv, char **env_var)
{
	int		i;
	t_shell	shell;

	i = 0;
	(void)argc;
	(void)argv;
	(void)env_var;
	ft_bzero(&shell, sizeof(t_shell));
	while (1)
	{
		shell.prompt = readline(CYAN"minishell> "RESET);
		check_builtin(&shell);
		free(shell.prompt);
	}
}
