/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:51:47 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/24 17:17:20 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_tmp(t_shell *shell, int env_len, int cmd_len)
{
	int 	i;
	char	**split_tmp;
	int		i_aux;
	char	***tmp;

	i = 0;
	tmp = malloc(sizeof(char **) * (env_len + cmd_len)); // LEAK: PUEDE DAR 1 LEAK
	cmd_len = 0;
	while (shell->env_variables[i])
	{
		tmp[i] = malloc(sizeof(char *) * 2);
		tmp[i][0] = ft_strdup(shell->env_variables[i][0]);
		tmp[i][1] = ft_strdup(shell->env_variables[i][1]);
		i++;
	}
	cmd_len = 1;
	while (shell->cmd[cmd_len])
	{
		if (ft_strchr(shell->cmd[cmd_len], '='))
		{
			split_tmp = ft_split(shell->cmd[cmd_len], '=');
			tmp[i] = malloc(sizeof(char *) * 2);
			tmp[i][0] = ft_strdup(split_tmp[0]);
			if (split_tmp[1])
				tmp[i][1] = ft_strdup(join_array(split_tmp, 1));
			else
				tmp[i][1] = ft_strdup("\0");
			i_aux = 0;
			while (split_tmp[i_aux])
			{
				free(split_tmp[i_aux]);
				i_aux++;
			}
		}
		cmd_len++;
		i++;
	}
	free(split_tmp);
	tmp[i] = NULL;
	free_array(shell->env_variables);
	shell->env_variables = tmp;
	i = 0;
	while (shell->env_variables[i])
	{
		printf("%s=%s\n", shell->env_variables[i][0], shell->env_variables[i][1]);
		i++;
	}
}

void	ft_export(t_shell *shell)
{
	int		i;
	int		env_len;
	int		cmd_len;
	
	i = 0;
	env_len = 0;
	cmd_len = 0;
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
		if (ft_strchr(shell->prompt, '='))
		{
			while (shell->env_variables[env_len])
				env_len++;
			while (shell->cmd[cmd_len])
				cmd_len++;
			create_tmp(shell, env_len, cmd_len);
		
		}
	}
}

/* static void	create_env_variables(t_shell *shell, char ***tmp, int i, int len)
{
	shell->env_variables = malloc(sizeof(char **) * (i + len));
	i = 0;
	while (tmp[i])
	{
		shell->env_variables[i] = malloc(sizeof(char *) * 2);
		shell->env_variables[i][0] = ft_strdup(tmp[i][0]);
		if (tmp[i][1])
			shell->env_variables[i][1] = ft_strdup(tmp[i][1]);
		else
			shell->env_variables[i][1] = ft_strdup("\0");
		i++;
	}
	shell->env_variables[i] = NULL;
	//free_array(tmp);
} */