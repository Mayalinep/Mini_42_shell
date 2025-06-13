/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:48:31 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:49:22 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !key)
		return (0);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
