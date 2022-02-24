/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:54:34 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/24 19:07:25 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/stat.h>

# define DQT 	'"'
# define SQT	'\''
# define SPC	' '

typedef struct s_shell
{
	char	*prompt;
	char	***env_variables;
	char	**cmd;
	int		flag;
	int		isvoid;
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
void		ft_pwd(void);
void		ft_echo(t_shell *shell);
void		ft_export(t_shell *shell);
void		ft_env(t_shell *shell);
void		ft_exit(t_shell *shell);

// Signal handlers
void		sigint_handler(int sig);

//Parseo
char		**parse_prompt(t_shell *shell, char *prompt);
int			even_quotes(t_shell *shell);
int			num_str(char *prompt, t_aux_parse *parse);

// Utils
void		free_array(char ***array);
int			ft_isdigit_str(char *str);
char	  *join_array(char **array, int start, char restorable_divider);

// Launcher
char		**find_env_variable(char *name, t_shell *shell);
char		*search_program_on_path(t_shell *shell);

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