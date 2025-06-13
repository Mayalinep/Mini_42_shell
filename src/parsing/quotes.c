/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:52 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:52:54 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_special_chars(char *str, int pos, int in_double_quote)
{
	if (in_double_quote)
	{
		if (str[pos] == '\\' && (str[pos + 1] == '"' || str[pos + 1] == '\\'
				|| str[pos + 1] == '$' || str[pos + 1] == '`'))
			return (1);
	}
	return (0);
}

static int	is_escaped_quote(char *str, int pos, int in_double_quote)
{
	int	backslash_count;
	int	i;

	if (pos == 0)
		return (0);
	if (str[pos - 1] == '\\')
	{
		if (in_double_quote && !handle_special_chars(str, pos - 1,
				in_double_quote))
			return (0);
		backslash_count = 0;
		i = pos - 1;
		while (i >= 0 && str[i] == '\\')
		{
			backslash_count++;
			i--;
		}
		if (backslash_count % 2 == 1)
			return (1);
		return (0);
	}
	return (0);
}

// Cette fonction gère juste le changement d'état des guillemets
static int	check_quote(char c, int *in_single, int *in_double)
{
	if (c == '\'')
	{
		*in_single = !(*in_single);
		return (*in_single);
	}
	if (c == '"')
	{
		*in_double = !(*in_double);
		return (*in_double * 2);
	}
	return (0);
}

// Cette fonction fait la boucle principale
int	get_quote_type_at_position(char *cmd, int pos)
{
	int	i;
	int	in_single;
	int	in_double;
	int	type;

	i = 0;
	in_single = 0;
	in_double = 0;
	type = 0;
	while (i < pos)
	{
		if (!is_escaped_quote(cmd, i, in_double))
			type = check_quote(cmd[i], &in_single, &in_double);
		i++;
	}
	return (type);
}

int	check_unclosed_quotes(char *command)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (command[i])
	{
		if (!is_escaped_quote(command, i, in_double_quote))
		{
			if (command[i] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
			else if (command[i] == '"' && !in_single_quote)
				in_double_quote = !in_double_quote;
		}
		i++;
	}
	if (in_single_quote || in_double_quote)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}
