/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:49:46 by gaguado-          #+#    #+#             */
/*   Updated: 2022/03/10 19:18:36 by gaguado-         ###   ########.fr       */
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

static void	decimicer(char *str, char **ret, int from, int upto)
{
	char	*var_name;
	char	*temp2;

	temp2 = ft_substr(str, from, upto);
	var_name = *ret;
	*ret = ft_strjoin(var_name, temp2);
	free(temp2);
	free(var_name);
}

char	*replace_dollar_variable_in_string(char *s, t_shell *shell)
{
	char	*ret;
	char	*var_name;
	int		i;
	int		z;

	i = 0;
	if (s[i] != '$')
		while (s[i] != '\0' && s[i] != '$')
			i++;
	ret = ft_substr(s, 0, i);
	while (ft_strchr(&s[i], '$'))
	{
		z = i + 1;
		while (s[z] != '\0' && (ft_isalnum(s[z]) || s[z] == '_' || s[z] == '?'))
			z++;
		var_name = ft_substr(s, i + 1, z - i - 1);
		ret = replace_with_env(&ret, var_name, shell);
		free(var_name);
		i = z - 1;
		while (s[z] != '\0' && s[z] != '$')
			z++;
		decimicer(s, &ret, i + 1, z - i - 1);
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
