/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:54:34 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/28 16:46:23 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

# define C_DQ 	'"'
# define C_SQ	'\''
# define C_SP	' '
# define C_EQ	'='

typedef struct s_shell
{
	char	*prompt;
	char	***env_variables;
	char	**cmd;
	int		isvoid;
	char	*currently_running_cmd_path;
	int		last_process_result;
	char	*history_file_route;
	pid_t	running_process_pid;
	int		isbuiltin;
}				t_shell;

typedef struct s_aux_parse
{
	int		i;
	int		x;
	int		check;
	int		start;
	int		len;
	int		num_str;
}				t_aux_parse;

// Builtins
void		ft_pwd(t_shell *shell);
void		ft_cd(t_shell *shell);
void		ft_echo(t_shell *shell);
void		ft_exit(t_shell *shell);
void		ft_env(t_shell *shell);
void		ft_export(t_shell *shell);
void		ft_unset(t_shell *shell);
void		delete_env_variable(t_shell *shell, char **env_var_to_delete);

// Signal handlers
void		sigint_handler(int sig);

// Parse
char		**parse_prompt(t_shell *shell, char *prompt);
int			even_quotes(t_shell *shell);
int			num_str(char *prompt, t_aux_parse *parse);
void		check_for_env_vars(char **cmd, t_shell *shell, t_aux_parse *parse);

// Utils
char		*join_array(char **array, int start, char restorable_divider);
void		free_matrix(char ***array);
void		free_array(char **array);
void		print_name(void);
int			ft_isdigit_str(char *str);

// Launcher
char		**find_env_variable(char *name, t_shell *shell);
char		*search_program_on_path(t_shell *shell);
void		handle_command(t_shell *shell);

# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define W_B_WHITE			"\x1b[47m"
# define W_B_CYAN			"\x1b[46m"
# define W_B_PURPLE			"\x1b[45m"
# define W_B_BLUE			"\x1b[44m"
# define W_B_YELLOW			"\x1b[43m"
# define W_B_GREEN			"\x1b[42m"
# define W_B_RED			"\x1b[41m"
# define WH_B_CLEAR			"\x1b[40m"
# define INVISIBLE			"\x1b[8m"
# define WHITE_BOX			"\x1b[7m"
# define WHITE_SUB			"\x1b[4m"
# define WHITE_CURS			"\x1b[3m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

#endif