/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/17 19:37:07 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_cmd(t_shell *shell)
{
	int i;

	i = 0;
	if (!ft_strncmp(shell->cmd[i], "pwd", 3) && shell->cmd[1] == 0)
		ft_pwd();
	else if (!ft_strncmp(shell->cmd[i], "echo", 4))
		ft_echo(shell);
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
		shell.cmd = parse_prompt(&shell);
		check_cmd(&shell);
		i = 0;
		while (shell.cmd[i])
		{
			printf("%s\n", shell.cmd[i]);
			i++;
		}
		free(shell.prompt);
	}
}
