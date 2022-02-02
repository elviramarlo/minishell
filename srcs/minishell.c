/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/02 19:47:21 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env_var)
{
	int		i;
	char	*prompt;

	i = 0;
	(void)argc;
	(void)argv;
	(void)env_var;
	while (1)
	{
		prompt = readline(BLUE"minishell> "RESET);
		printf("%s\n", prompt);
		free(prompt);
	}
}
