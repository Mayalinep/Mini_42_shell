/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:10 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:52:12 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Ajoute un caractère à la nouvelle chaîne
** Retourne 1 en cas de succès, 0 en cas d'erreur
*/
int	add_char(char **str, char c)
{
	char	*temp;
	char	c_str[2];

	c_str[0] = c;
	c_str[1] = '\0';
	temp = ft_strjoin(*str, c_str);
	if (!temp)
		return (0);
	free(*str);
	*str = temp;
	return (1);
}

/*
** Gère l'expansion de la variable $?
** Retourne la chaîne contenant le code de retour ou NULL en cas d'erreur
*/
static char	*handle_exit_status_var(t_shell *shell)
{
	char	*tmp;

	tmp = ft_itoa(shell->exit_status);
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*
** Gère l'expansion d'une variable d'environnement normale
** Retourne la valeur de la variable ou une chaîne vide si non trouvée
*/
static char	*handle_env_var(t_shell *shell, char *var_name)
{
	char	*value;
	char	*tmp;

	value = get_env_value(shell->env, var_name);
	if (value)
		tmp = ft_strdup(value);
	else
		tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*
** Ajoute une variable d'environnement à la chaîne en cours de construction
** Gère à la fois $? et les variables d'environnement normales
*/
int	add_expanded_var(t_shell *shell, char *var_name, char **new_str)
{
	char	*value;
	char	*tmp;

	if (ft_strcmp(var_name, "?") == 0)
		tmp = handle_exit_status_var(shell);
	else
		tmp = handle_env_var(shell, var_name);
	if (!tmp)
		return (ERROR);
	value = ft_strjoin(*new_str, tmp);
	free(tmp);
	free(*new_str);
	if (!value)
		return (ERROR);
	*new_str = value;
	return (SUCCESS);
}
