/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/10 19:24:36 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Gestionar espacios antes o después de los comandos

static void	check_prompt(char *prompt)
{
	if (ft_strcmp(prompt, "pwd"))
		get_cwd();
	else
		printf("%s\n", prompt);
}

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
		prompt = readline(CYAN"minishell> "RESET);
		check_prompt(prompt);
		free(prompt);
	}
}
