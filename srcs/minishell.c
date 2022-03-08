/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/08 20:57:44 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pos_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	if ((shell->cmd[0][0] == '>' && shell->cmd[1][0] == '>')
		|| (shell->cmd[0][0] == '<' && shell->cmd[1][0] == '<'))
		return (3);
	else if (shell->cmd[0][0] == '>' || shell->cmd[0][0] == '<')
		return (2);
	else
		return (0);
}

void	check_is_builtin(t_shell *shell)
{
	shell->isbuiltin = 0;
	if (!shell->isvoid)
	{
		if (!even_quotes(shell))
			ft_error(ft_strdup("minishell: error: odd quotes"), 1, shell);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "pwd"))
			ft_pwd(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "echo"))
			ft_echo(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "export"))
			ft_export(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "unset"))
			ft_unset(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "exit"))
			ft_exit(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "env")
			&& shell->cmd[pos_cmd(shell) + 1] == 0)
			ft_env(shell);
		else if (ft_strcmp(shell->cmd[0], "cd"))
			ft_cd(shell, &shell->cmd[pos_cmd(shell)]);
	}
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

	signal(SIGINT, sigint_handler);
	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	add_enviroment_variables_to_shell(&shell, env_var);
	print_name();
	initialize_history(&shell);
	while (1)
	{
		shell.errnum = 0;
		shell.prompt = readline(CYAN"minishell> "RESET);
		if (!shell.prompt)
			exit(EXIT_SUCCESS);
		add_to_history(shell.prompt, &shell);
		shell.cmd_backlog = parse_prompt(&shell, shell.prompt);
		handle_pipes_and_command(&shell);

		free(shell.prompt);
		//free_array(shell.cmd);
		//system("leaks minishell");
	}
}
