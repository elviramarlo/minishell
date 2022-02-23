/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/23 15:49:55 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->isvoid)
	{
		if (!ft_strncmp(shell->cmd[i], "pwd", 3) && shell->cmd[1] == 0)
			ft_pwd();
		else if (!ft_strncmp(shell->cmd[i], "echo", 4))
		{
			ft_echo(shell);
			return (1);
		}
		else if (!ft_strncmp(shell->cmd[i], "export", 6))
		{
			ft_export(shell);
			return (1);
		}
		else if (!ft_strncmp(shell->cmd[i], "exit", 4))
		{
			ft_exit();
			return (1);
		}
		else
		{
			while (shell->cmd[i])
			{
				printf("%s\n", shell->cmd[i]);
				i++;
			}
		}
	}
}

int	main(int argc, char **argv, char **env_var)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)env_var;
	ft_bzero(&shell, sizeof(t_shell));
	while (1)
	{
		shell.prompt = readline(CYAN"minishell> "RESET);
		shell.cmd = parse_prompt(&shell, shell.prompt);
		if (!check_cmd(&shell))
			printf("Command goes running goes here");
		free(shell.prompt);
	/* 	int i = 0;
		i = 0;
		while (env_var[i])
		{
			printf("%s\n", env_var[i]);
			i++;
		} */
	}
}
