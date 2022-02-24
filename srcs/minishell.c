/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/23 16:41:45 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->isvoid)
	{
		if (!ft_strncmp(shell->cmd[i], "pwd", 3) && shell->cmd[1] == 0
			&& ft_strlen(shell->cmd[i]) == 3)
		{
			ft_pwd();
			return (1);
		}
		else if (!ft_strncmp(shell->cmd[i], "echo", 4)
			&& ft_strlen(shell->cmd[i]) == 4)
		{
			ft_echo(shell);
			return (1);
		}
		else if (!ft_strncmp(shell->cmd[i], "export", 6)
			&& ft_strlen(shell->cmd[i]) == 6)
		{
			ft_export(shell);
			return (1);
		}
		else if (!ft_strncmp(shell->cmd[i], "exit", 4)
			&& ft_strlen(shell->cmd[i]) == 4)
		{
			ft_exit(shell);
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
	return (0);
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
		shell->env_variables[i][0] = ft_strdup(temp[0]);
		shell->env_variables[i][1] = join_array(temp, 1, '=');
		free(temp);
		i++;
	}
	shell->env_variables[i] = NULL;
}

int	main(int argc, char **argv, char **env_var)
{
	t_shell	shell;
	int i = 0;

	signal(SIGINT, sigint_handler);
	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	add_enviroment_variables_to_shell(&shell, env_var);
	add_history(NULL);
	while (shell.env_variables[i])
	{
		printf("ENV Vars: %s=%s\n", shell.env_variables[i][0], shell.env_variables[i][1]);
		i++;
	}
	while (1)
	{
		shell.prompt = readline(CYAN"minishell> "RESET);
		add_history(shell.prompt);
		if (!shell.prompt)
			exit(EXIT_SUCCESS);
		shell.cmd = parse_prompt(&shell, shell.prompt);
		if (!check_cmd(&shell))
		{
			// shell.running_process_pid = fork();
			printf("%s\n", search_program_on_path(&shell));
		}
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
