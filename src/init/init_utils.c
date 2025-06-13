/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:59 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:52:01 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**extract_key_value(char *env_var)
{
	char	**result;
	char	*equal_pos;

	if (!env_var)
		return (NULL);
	equal_pos = ft_strchr(env_var, '=');
	if (!equal_pos)
		return (NULL);
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_substr(env_var, 0, equal_pos - env_var);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = ft_strdup(equal_pos + 1);
	if (!result[1])
	{
		free(result[0]);
		free(result);
		return (NULL);
	}
	return (result);
}

t_env	*create_env_node(char *env_var)
{
	t_env	*node;
	char	**key_value;

	if (!env_var)
		return (NULL);
	key_value = extract_key_value(env_var);
	if (!key_value)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key_value[0]);
		free(key_value[1]);
		free(key_value);
		return (NULL);
	}
	node->key = key_value[0];
	node->value = key_value[1];
	node->next = NULL;
	free(key_value);
	return (node);
}

int	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return (ERROR);
	if (!*env)
	{
		*env = new_node;
		return (SUCCESS);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (SUCCESS);
}
