/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:27:03 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/26 00:56:34 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	find_env_var_to_delete(t_shell *shell, char **env_var_to_delete)
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

/* 	i = 0;
	while (shell->env_variables[i])
	{
		printf("%s=%s\n", shell->env_variables[i][0],
			shell->env_variables[i][1]);
		i++;
	} */

void	ft_unset(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (ft_strchr(shell->cmd[i], '='))
			printf(RED"unset: '%s': not a valid identifier\n"RESET,
				shell->cmd[i]);
		else if (find_env_variable(shell->cmd[i], shell))
			find_env_var_to_delete(shell, find_env_variable(shell->cmd[i],
					shell));
		i++;
	}
}
