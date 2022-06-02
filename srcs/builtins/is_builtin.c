/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:44 by elvmarti          #+#    #+#             */
/*   Updated: 2022/05/19 00:10:17 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_is_builtin(t_shell *shell)
{
	shell->isbuiltin = 0;
	if (!shell->isvoid)
	{
		if (!even_quotes(shell))
			ft_error(ft_strdup("minishell: error: odd quotes"), 1, shell);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "pwd"))
			ft_pwd(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "echo"))
			ft_echo(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "export"))
			ft_export(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "unset"))
			ft_unset(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "exit"))
			ft_exit(shell, &shell->cmd[pos_cmd(shell)]);
		else if (ft_strcmp(shell->cmd[pos_cmd(shell)], "env")
			&& shell->cmd[pos_cmd(shell) + 1] == 0)
			ft_env(shell);
		else if (ft_strcmp(shell->cmd[0], "cd"))
			ft_cd(shell, &shell->cmd[pos_cmd(shell)]);
	}
}

int	parent_process_command(t_shell *shell)
{
	if (shell->cmd[pos_cmd(shell)] && (ft_strcmp(shell->cmd[pos_cmd(shell)], "exit")
			|| ft_strcmp(shell->cmd[pos_cmd(shell)], "cd")
			|| ft_strcmp(shell->cmd[pos_cmd(shell)], "export")
			|| ft_strcmp(shell->cmd[pos_cmd(shell)], "unset")))
		return (1);
	else
		return (0);
}
