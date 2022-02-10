/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:07:20 by elvmarti          #+#    #+#             */
/*   Updated: 2022/02/10 18:08:35 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cwd(void)
{
	char	cwd[500];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("Error\n");
	else
		printf("%s\n", cwd);
}
