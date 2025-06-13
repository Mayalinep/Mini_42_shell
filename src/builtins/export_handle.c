/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:12:26 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 10:17:27 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_with_plus(t_shell *shell, char *key, char *value)
{
	char	*key_value;
	char	*new_value;

	key_value = get_env_value(shell->env, key);
	if (key_value)
	{
		new_value = gc_strjoin(shell->gc, key_value, value);
		if (!new_value)
			return (ERROR);
		if (set_env_value(&shell->env, key, new_value))
			return (ERROR);
		return (SUCCESS);
	}
	else
		return (set_env_value(&shell->env, key, value));
}

int	handle_key_arg(t_shell *shell, char **args)
{
	char	*key;
	char	*plus;

	plus = ft_strchr(args[0], '+');
	if (plus)
	{
		key = gc_substr(shell->gc, args[0], 0, (size_t)(plus - args[0]));
		if (!handle_with_plus(shell, key, args[1]))
			return (SUCCESS);
		return (ERROR);
	}
	else
		return (set_env_value(&shell->env, args[0], args[1]));
}

char	**handle_no_equal(t_gc *gc, char *value)
{
	char	**args;

	if (!value || !*value)
		return (NULL);
	args = gc_calloc(gc, 3, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = gc_strdup(gc, value);
	if (!args[0])
		return (NULL);
	args[1] = NULL;
	args[2] = NULL;
	return (args);
}

char	**handle_with_equal(t_gc *gc, char *value, char *equal_pos)
{
	char	**args;

	if (!gc || !value || !equal_pos)
		return (NULL);
	if (!value || !*value || !equal_pos || equal_pos == value)
		return (NULL);
	args = gc_calloc(gc, 3, sizeof(char *));
	if (!args)
		return (NULL);
	*equal_pos = '\0';
	args[0] = gc_strdup(gc, value);
	args[1] = gc_strdup(gc, equal_pos + 1);
	*equal_pos = '=';
	if (!args[0] || !args[1])
		return (NULL);
	args[2] = NULL;
	return (args);
}
