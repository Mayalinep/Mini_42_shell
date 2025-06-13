/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:21 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/07 10:49:59 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_env_var(t_env **env, t_env *new)
{
	t_env	*current;

	if (!env || !new)
		return (ERROR);
	if (!*env)
	{
		*env = new;
		return (SUCCESS);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	return (SUCCESS);
}

int	modify_env_value(t_env *current, char *value)
{
	if (current->value)
		free(current->value);
	if (value)
		current->value = ft_strdup(value);
	else
		current->value = NULL;
	if (value && !current->value)
		return (ERROR);
	return (SUCCESS);
}

int	create_env_var(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (ERROR);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), ERROR);
	}
	else
		new->value = NULL;
	new->next = NULL;
	add_env_node(env, new);
	return (SUCCESS);
}

int	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*current;

	if (!env || !key)
		return (0);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (modify_env_value(current, value));
		current = current->next;
	}
	return (create_env_var(env, key, value));
}
