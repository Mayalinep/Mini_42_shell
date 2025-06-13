/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: data_lyla <data_lyla@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:50:39 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/03 02:08:21 by data_lyla        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Recherche une variable d'environnement par sa clé
** Retourne la valeur de la variable ou NULL si non trouvée
** Gère le cas spécial de PWD en le mettant à jour avec getcwd
*/

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;
	char	*current_pwd;

	if (!env || !key)
		return (NULL);
	if (ft_strcmp(key, "PWD") == 0)
	{
		current_pwd = getcwd(NULL, 0);
		if (current_pwd)
		{
			set_env_value(&env, "PWD", current_pwd);
			free(current_pwd);
		}
	}
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
