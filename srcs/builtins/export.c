/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:51:47 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/10 18:22:01 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	***add_env_variables(char ***tmp, int i, char **cmd, t_shell *shell)
{
	int		len;
	char	**split_tmp;

	len = 1;
	while (cmd[len] && cmd[len][0] != '>' &&  cmd[len][0] != '<')
	{
		if (!ft_isalnum_str(cmd[len], '='))
		{
			ft_putstr_fd("export: ", 2);
			ft_error(ft_strjoin(cmd[len], ": not a valid identifier"), 1, shell);
		}
		else if (ft_strchr(cmd[len], C_EQ) && cmd[len][0] != C_EQ)
		{
			split_tmp = ft_split(cmd[len], C_EQ);
			tmp[i] = malloc(sizeof(char *) * 2);
			tmp[i][0] = ft_strdup(split_tmp[0]);
			if (split_tmp[1])
				tmp[i][1] = ft_strdup(join_array(split_tmp, 1, 0));
			else
				tmp[i][1] = ft_strdup("\0");
			free_array(split_tmp);
			i++;
		}
		if (cmd[len][0] == C_EQ)
		{
			ft_putstr_fd("export: ", 2);
			ft_error(ft_strjoin(cmd[len], ": not a valid identifier"), 1, shell);
		}
		len++;
	}
	tmp[i] = NULL;
	return (tmp);
}

static void	create_array_env_variable(t_shell *shell, int env_len, int cmd_len, char **cmd)
{
	int		i;
	char	***tmp;

	i = 0;
	tmp = malloc(sizeof(char **) * (env_len + cmd_len));
	while (shell->env_variables[i])
	{
		tmp[i] = malloc(sizeof(char *) * 2);
		tmp[i][0] = ft_strdup(shell->env_variables[i][0]);
		tmp[i][1] = ft_strdup(shell->env_variables[i][1]);
		i++;
	}
	tmp = add_env_variables(tmp, i, cmd, shell);
	free_matrix(shell->env_variables);
	shell->env_variables = tmp;
}

static int	cmd_len(char **cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd[len])
	{
		if (!ft_strchr(cmd[len], C_EQ) && len > 0)
			i++;
		len++;
	}
	return (len - i);
}

static void	check_if_var_already_exists(t_shell *shell, char **cmd)
{
	char	**tmp_slipt;
	int		i;

	i = 1;
	while (cmd[i])
	{
		tmp_slipt = ft_split(cmd[i], C_EQ);
		if (find_env_variable(tmp_slipt[0], shell))
			delete_env_variable(shell, tmp_slipt);
		i++;
		free_array(tmp_slipt);
	}
}

void	ft_export(t_shell *shell, char **cmd)
{
	int		i;
	int		env_len;

	i = 0;
	env_len = 0;
	if (!cmd[1])
	{
		while (shell->env_variables[i])
		{
			printf("declare -x %s=\"%s\"\n", shell->env_variables[i][0],
				shell->env_variables[i][1]);
			i++;
		}
	}
	else
	{
		check_if_var_already_exists(shell, cmd);
		while (shell->env_variables[env_len])
			env_len++;
		create_array_env_variable(shell, env_len, cmd_len(cmd), cmd);
	}
	shell->isbuiltin = 1;
}
