/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:48:44 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/09 17:08:38 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_var_home(t_shell *shell, char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (!ft_strcmp(shell->env_variables[i][0], "HOME"))
		i++;
	if (ft_strlen(cmd[1]) < 3)
		chdir(shell->env_variables[i][1]);
	else
	{
		tmp = ft_substr(cmd[1], 2, ft_strlen(cmd[1]));
		tmp2 = ft_strjoin(shell->env_variables[i][1], "/");
		if (chdir(ft_strjoin(tmp2, tmp)) == -1)
			ft_error(ft_strjoin("cd: ", strerror(errno)), errno, shell);
		free(tmp);
		free(tmp2);
	}
}

void	ft_cd(t_shell *shell, char **cmd)
{
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "~/", 2))
			cd_var_home(shell, cmd);
		else if (chdir(cmd[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_error(ft_strjoin(cmd[1], ": No such file or directory"),
				errno, shell);
			printf("%d\n", errno);
		}
	}
	shell->isbuiltin = 1;
}
