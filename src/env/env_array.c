/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: data_lyla <data_lyla@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:50:02 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/03 01:51:33 by data_lyla        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Compte le nombre de variables d'environnement
*/
int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
** Crée une chaîne "KEY=VALUE" pour une variable d'environnement
*/
static char	*create_env_string(t_env *node)
{
	char	*result;
	int		len;

	len = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, node->key, len);
	ft_strlcat(result, "=", len);
	ft_strlcat(result, node->value, len);
	return (result);
}

/*
** Convertit la liste d'environnement en tableau de chaînes
** Retourne le tableau ou NULL en cas d'erreur
*/
char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		count;
	int		i;
	t_env	*current;

	count = count_env_vars(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		env_array[i] = create_env_string(current);
		if (!env_array[i])
		{
			free_env_array(env_array);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/*
** Libère le tableau d'environnement créé par env_to_array
*/
void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
