/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:45:22 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/14 17:31:33 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_term(t_shell *shell)
{
	struct termios	t;
	char			**shell_lvl;
	int				lvl;
	char			*temp;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	shell_lvl = find_env_variable("SHLVL", shell);
	lvl = ft_atoi(shell_lvl[1]);
	temp = shell_lvl[1];
	free(temp);
	shell_lvl[1] = ft_itoa(lvl + 1);
}
