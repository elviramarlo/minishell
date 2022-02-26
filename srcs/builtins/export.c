/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:51:47 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/25 17:13:43 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// FALTA CAMBIAR EL VALOR SI EXISTE EL NOMBRE Y QUE DÉ ERROR SI METES UN
// VALOR PERO SIN NOMBRE

static char	***add_env_variables(t_shell *shell, char ***tmp, int i)
{
	int		cmd_len;
	char	**split_tmp;

	cmd_len = 1;
	while (shell->cmd[cmd_len])
	{
		if (ft_strchr(shell->cmd[cmd_len], '='))
		{
			split_tmp = ft_split(shell->cmd[cmd_len], '=');
			tmp[i] = malloc(sizeof(char *) * 2);
			tmp[i][0] = ft_strdup(split_tmp[0]);
			if (split_tmp[1])
				tmp[i][1] = ft_strdup(join_array(split_tmp, 1, 0));
			else
				tmp[i][1] = ft_strdup("\0");
			free_array(split_tmp);
			i++;
		}
		cmd_len++;
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
	i = 0;
	while (shell->env_variables[i])
	{
		printf("%s=%s\n", shell->env_variables[i][0],
			shell->env_variables[i][1]);
		i++;
	}
}

static int	cmd_len(t_shell *shell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (shell->cmd[len])
	{
		if (!ft_strchr(shell->cmd[len], '=') && len > 0)
			i++;
		len++;
	}
	return (len - i);
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
	else if (ft_strchr(shell->prompt, '='))
	{
		while (shell->env_variables[env_len])
			env_len++;
		create_array_env_variable(shell, env_len, cmd_len(shell));
	}
}
