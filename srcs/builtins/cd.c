/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:48:44 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/28 16:45:31 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_var_home(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (!ft_strcmp(shell->env_variables[i][0], "HOME"))
		i++;
	if (ft_strlen(shell->cmd[1]) < 3)
		chdir(shell->env_variables[i][1]);
	else
	{
		tmp = ft_substr(shell->cmd[1], 2, ft_strlen(shell->cmd[1]));
		tmp2 = ft_strjoin(shell->env_variables[i][1], "/");
		if (chdir(ft_strjoin(tmp2, tmp)) == -1)
			printf(RED"cd: %s: No such file or directory\n"RESET,
				shell->cmd[1]);
		free(tmp);
		free(tmp2);
	}
}

void	ft_cd(t_shell *shell)
{
	if (shell->cmd[1])
	{
		if (!ft_strncmp(shell->cmd[1], "~/", 2))
			cd_var_home(shell);
		else if (chdir(shell->cmd[1]) == -1)
			printf(RED"cd: %s: No such file or directory\n"RESET,
				shell->cmd[1]);
	}
	shell->isbuiltin = 1;
}
