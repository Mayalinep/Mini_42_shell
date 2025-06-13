/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:19 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:52:22 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_quotes_internal(t_shell *shell, char c, char **new_str)
{
	if (c == '\'' && !shell->quotes.in_double_quote)
	{
		shell->quotes.in_single_quote = !shell->quotes.in_single_quote;
		if (!add_char(new_str, c))
			return (0);
		return (1);
	}
	if (c == '"' && !shell->quotes.in_single_quote)
	{
		shell->quotes.in_double_quote = !shell->quotes.in_double_quote;
		if (!add_char(new_str, c))
			return (0);
		return (1);
	}
	return (2);
}

static int	process_char_internal(t_shell *shell, char *line, int *i,
		char **new_str)
{
	if (line[*i] == '$')
	{
		if (!handle_variable_expansion(shell, line, i, new_str))
			return (0);
		return (1);
	}
	if (!add_char(new_str, line[*i]))
		return (0);
	(*i)++;
	return (1);
}

// Nouvelle fonction pour la boucle principale
static int	process_expansion_loop(t_shell *shell, char *line, char **new_str)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i])
	{
		ret = handle_quotes_internal(shell, line[i], new_str);
		if (ret == 0)
			return (ERROR);
		if (ret == 1)
		{
			i++;
			continue ;
		}
		if (!process_char_internal(shell, line, &i, new_str))
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** Remplace les variables d'environnement ($VAR) par leur valeur
** Gère aussi $? pour le code de retour
** Retourne 1 en cas de succès, 0 en cas d'erreur
*/
int	expand_variables(t_shell *shell, char **line)
{
	char	*new_str;

	if (!line || !*line)
		return (ERROR);
	new_str = ft_strdup("");
	if (!new_str)
		return (ERROR);
	if (process_expansion_loop(shell, *line, &new_str) == ERROR)
	{
		free(new_str);
		return (ERROR);
	}
	free(*line);
	*line = new_str;
	return (SUCCESS);
}
