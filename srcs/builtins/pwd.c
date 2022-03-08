/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:07:20 by elvmarti          #+#    #+#             */
/*   Updated: 2022/03/08 16:36:41 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[4096];
	if (!shell->cmd[1])
	{
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_error(ft_strdup("minishell: error with pwd"), errno, shell);
	else
		printf("%s\n", cwd);
	shell->isbuiltin = 1;
	}
}
