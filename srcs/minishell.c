/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/10 19:49:59 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_is_interactive = 0;

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
		temp = ft_split(env_var[i], C_EQ);
		shell->env_variables[i] = malloc(sizeof(char *) * 2);
		shell->env_variables[i][0] = ft_strdup(temp[0]);
		shell->env_variables[i][1] = join_array(temp, 1, C_EQ);
		free(temp[0]);
		free(temp);
		i++;
	}
	shell->env_variables[i] = NULL;
}

void	initialize_history(t_shell *shell)
{
	char	*home_path;
	char	*read_history_line;
	int		fd;

	home_path = find_env_variable("HOME", shell)[1];
	shell->history_file_route = ft_strjoin(home_path, "/.minishell_history");
	fd = open(shell->history_file_route, O_RDONLY | O_CREAT, 0644);
	while (get_next_line(fd, &read_history_line) > 0)
	{
		if (read_history_line)
			add_history(read_history_line);
		free(read_history_line);
	}
	free(read_history_line);
	close(fd);
}

void	add_to_history(char *to_add, t_shell *shell)
{
	int	fd;

	fd = open(shell->history_file_route, O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(fd, to_add, ft_strlen(to_add));
	write(fd, "\n", 1);
	close(fd);
	add_history(to_add);
}

int	main(int argc, char **argv, char **env_var)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	add_signal_handlers();
	ft_bzero(&shell, sizeof(t_shell));
	add_enviroment_variables_to_shell(&shell, env_var);
	print_name();
	setup_term();
	initialize_history(&shell);
	while (1)
	{
		g_is_interactive = 1;
		shell.prompt = readline(CYAN"minishell> "RESET);
		g_is_interactive = 0;
		if (!shell.prompt)
			exit(EXIT_SUCCESS);
		add_to_history(shell.prompt, &shell);
		shell.cmd_backlog = parse_prompt(&shell, shell.prompt);
		if (!shell.isvoid)
			handle_pipes_and_command(&shell);
		free(shell.prompt);
		if (!shell.isvoid)
			free_array(shell.cmd_backlog);
	}
}
