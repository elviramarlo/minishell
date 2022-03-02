/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:49:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/02/28 19:58:32 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dollar_question_mark(char **str, char *name, t_shell *shell)
{
	char	*ret;
	char	*temp;

	ret = *str;
	temp = ft_itoa(shell->last_process_result);
	ret = ft_strjoin(ret, temp);
	free(temp);
	temp = ret;
	ret = ft_strjoin(ret, name + 1);
	free(temp);
	free(*str);
	return (ret);
}

static char	*replace_with_env(char **str, char *name, t_shell *shell)
{
	char	**env_var;
	char	*ret;

	ret = *str;
	if (ft_isdigit(name[0]))
	{
		ret = ft_strjoin(ret, name + 1);
		free(*str);
		return (ret);
	}
	if (name[0] == '?')
		return (handle_dollar_question_mark(str, name, shell));
	env_var = find_env_variable(name, shell);
	if (env_var)
		ret = ft_strjoin(ret, env_var[1]);
	else
		ret = ft_strjoin(ret, "");
	free(*str);
	return (ret);
}

static char	*replace_dollar_variable_in_string(char *str, t_shell *shell)
{
	char	*ret;
	char	*var_name;
	char	*temp2;
	int		i;
	int		z;

	i = 0;
	if (str[i] != '$')
		while (str[i] != '\0' && str[i] != '$')
			i++;
	ret = ft_substr(str, 0, i);
	while (ft_strchr(&str[i], '$'))
	{
		z = i + 1;
		while (str[z] != '\0' && (ft_isalnum(str[z]) || str[z] == '_' || str[z] == '?'))
			z++;
		var_name = ft_substr(str, i + 1, z - i - 1);
		ret = replace_with_env(&ret, var_name, shell);
		free(var_name);
		i = z - 1;
		while (str[z] != '\0' && str[z] != '$')
			z++;
		temp2 = ft_substr(str, i + 1, z - i - 1);
		var_name = ret;
		ret = ft_strjoin(var_name, temp2);
		free(temp2);
		free(var_name);
		i = z;
	}
	return (ret);
}

void	check_for_env_vars(char **cmd, t_shell *shell, t_aux_parse *parse)
{
	char	*temp;

	if (shell->prompt[parse->i - 1] == C_SP)
		return ;
	if (shell->prompt[parse->i - 1] == C_SQ || !cmd[parse->x - 1])
		return ;
	if (shell->prompt[parse->i - 1] == C_SP
		&& shell->prompt[parse->i - 2] == C_SQ)
		return ;
	temp = cmd[parse->x - 1];
	cmd[parse->x - 1] = replace_dollar_variable_in_string(temp, shell);
	free(temp);
}
