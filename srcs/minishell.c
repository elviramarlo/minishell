/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/11 16:47:19 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Gestionar errores

static void	check_builtin(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->prompt[i] == ' ')
		i++;
	if (!ft_strncmp(&shell->prompt[i], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(&shell->prompt[i], "echo", 4))
		ft_echo(shell, &shell->prompt[i]);
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
