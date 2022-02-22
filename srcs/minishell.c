/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/22 18:23:19 by gaguado-         ###   ########.fr       */
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

void	add_enviroment_variables_to_shell(t_shell *shell, char **env_var)
{
	int		env_var_count;
	int		i;
	char	**temp;

	env_var_count = 0;
	i = 0;
	while (env_var[env_var_count])
		env_var_count++;
	shell->env_variables = malloc(sizeof(char **) * env_var_count + 1);
	while (env_var[i])
	{
		temp = ft_split(env_var[i], '=');
		shell->env_variables[i] = malloc(sizeof(char *) * 2);
		shell->env_variables[i][0] = temp[0];
		shell->env_variables[i][1] = join_array(temp, 1);
		free(temp);
		i++;
	}
	shell->env_variables[i] = NULL;
}

int	main(int argc, char **argv, char **env_var)
{
	int		i;
	t_shell	shell;

	signal(SIGINT, sigint_handler);
	i = 0;
	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	add_enviroment_variables_to_shell(&shell, env_var);
	add_history(NULL);
	while (1)
	{
		shell.prompt = readline(CYAN"minishell> "RESET);
		add_history(shell.prompt);
		if (!shell.prompt)
			exit(EXIT_SUCCESS);
		check_builtin(&shell);
		free(shell.prompt);
	}
}
