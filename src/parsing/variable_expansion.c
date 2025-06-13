/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:38 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/10 20:48:14 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_special_var(t_shell *shell, char *line, int *i, char **new_str)
{
	if (line[*i + 1] == '?')
	{
		if (!add_expanded_var(shell, "?", new_str))
			return (0);
		*i += 2;
		return (1);
	}
	return (0);
}

static int	process_variable_logic(t_shell *shell, char *var_name,
		char **new_str)
{
	if (get_env_value(shell->env, var_name))
	{
		if (!add_expanded_var(shell, var_name, new_str))
		{
			free(var_name);
			return (0);
		}
		return (1);
	}
	else
	{
		if (!add_char(new_str, '$'))
		{
			free(var_name);
			return (0);
		}
		return (2);
	}
}

int	handle_normal_var(t_shell *shell, char *line, int *i, char **new_str)
{
	char	*var_name;
	int		j;
	int		result;

	j = *i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	if (j == *i + 1)
	{
		if (!add_char(new_str, line[*i]))
			return (0);
		(*i)++;
		return (1);
	}
	var_name = ft_substr(line, *i + 1, j - *i - 1);
	if (!var_name)
		return (0);
	result = process_variable_logic(shell, var_name, new_str);
	if (result == 1)
		*i = j;
	else if (result == 2)
		(*i)++;
	free(var_name);
	return (result > 0);
}

int	handle_variable_expansion(t_shell *shell, char *line, int *i,
		char **new_str)
{
	if (shell->quotes.in_single_quote)
	{
		if (!add_char(new_str, line[*i]))
			return (0);
		(*i)++;
		return (1);
	}
	if (handle_special_var(shell, line, i, new_str))
		return (1);
	return (handle_normal_var(shell, line, i, new_str));
}
