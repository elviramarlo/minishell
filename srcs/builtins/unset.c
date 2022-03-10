/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:27:03 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/10 18:36:07 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_env_variable(t_shell *shell, char **env_var_to_delete)
{
	char	***tmp;
	int		env_len;
	int		i;

	i = 0;
	env_len = 0;
	while (shell->env_variables[env_len])
		env_len++;
	tmp = malloc(sizeof(char **) * (env_len));
	env_len = 0;
	while (shell->env_variables[env_len])
	{
		if (!ft_strcmp(shell->env_variables[env_len][0], env_var_to_delete[0]))
		{
			tmp[i] = malloc(sizeof(char *) * 2);
			tmp[i][0] = ft_strdup(shell->env_variables[env_len][0]);
			tmp[i][1] = ft_strdup(shell->env_variables[env_len][1]);
			i++;
		}
		env_len++;
	}
	tmp[i] = NULL;
	free_matrix(shell->env_variables);
	shell->env_variables = tmp;
}

void	ft_unset(t_shell *shell, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], C_EQ)
			|| !ft_isalnum_str(cmd[i], '='))
		{
			ft_putstr_fd("unset: ", 2);
			ft_error(ft_strjoin(cmd[i], ": not a valid identifier"), 1,
				shell);
		}
		else if (find_env_variable(cmd[i], shell))
			delete_env_variable(shell, find_env_variable(cmd[i],
					shell));
		i++;
	}
	shell->isbuiltin = 1;
}
