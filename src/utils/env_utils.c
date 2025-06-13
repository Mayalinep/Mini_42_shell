/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:48 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 00:06:42 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_exist(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	if (!key)
		return (0);
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}
