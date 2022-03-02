/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:51:47 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/28 19:38:53 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	***add_env_variables(t_shell *shell, char ***tmp, int i)
{
	int		len;
	char	**split_tmp;

	len = 1;
	while (shell->cmd[len])
	{
		if (!ft_isalnum_str(shell->cmd[len], '='))
			printf(RED"export: '%s': not a valid identifier\n"RESET,
				shell->cmd[len]);
		else if (ft_strchr(shell->cmd[len], C_EQ) && shell->cmd[len][0] != C_EQ)
		{
			split_tmp = ft_split(shell->cmd[len], C_EQ);
			tmp[i] = malloc(sizeof(char *) * 2);
			tmp[i][0] = ft_strdup(split_tmp[0]);
			if (split_tmp[1])
				tmp[i][1] = ft_strdup(join_array(split_tmp, 1, 0));
			else
				tmp[i][1] = ft_strdup("\0");
			free_array(split_tmp);
			i++;
		}
		if (shell->cmd[len][0] == C_EQ)
			printf(RED"export: '%s': not a valid identifier\n"RESET,
				shell->cmd[len]);
		len++;
	}
	tmp[i] = NULL;
	return (tmp);
}

static void	create_array_env_variable(t_shell *shell, int env_len, int cmd_len)
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
	tmp = add_env_variables(shell, tmp, i);
	free_matrix(shell->env_variables);
	shell->env_variables = tmp;
}

static int	cmd_len(t_shell *shell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (shell->cmd[len])
	{
		if (!ft_strchr(shell->cmd[len], C_EQ) && len > 0)
			i++;
		len++;
	}
	return (len - i);
}

static void	check_if_var_already_exists(t_shell *shell)
{
	char	**tmp_slipt;
	int		i;

	i = 1;
	while (shell->cmd[i])
	{
		tmp_slipt = ft_split(shell->cmd[i], C_EQ);
		if (find_env_variable(tmp_slipt[0], shell))
			delete_env_variable(shell, tmp_slipt);
		i++;
	}
	free_array(tmp_slipt);
}

void	ft_export(t_shell *shell)
{
	int		i;
	int		env_len;

	i = 0;
	env_len = 0;
	if (!shell->cmd[1])
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
		check_if_var_already_exists(shell);
		while (shell->env_variables[env_len])
			env_len++;
		create_array_env_variable(shell, env_len, cmd_len(shell));
	}
	shell->isbuiltin = 1;
}
