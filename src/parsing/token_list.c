/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:07 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/07 10:45:12 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

int	add_token_to_list(t_token **list, t_token *new_token)
{
	t_token	*current;

	if (!*list)
	{
		*list = new_token;
		return (1);
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
	return (1);
}

int	append_token(t_token **list, char *value, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->value = value;
	new_token->type = type;
	new_token->quote_type = get_quote_type(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (add_token_to_list(list, new_token));
}

void	copy_token(char *command, int length, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i] && i < length)
	{
		if (command[i] == '\'' && ++i)
		{
			while (command[i] != '\'' && i < length)
				str[j++] = command[i++];
			i++;
		}
		else if (command[i] == '"' && ++i)
		{
			while (command[i] != '"' && i < length)
				str[j++] = command[i++];
			i++;
		}
		else
			str[j++] = command[i++];
	}
	str[j] = '\0';
}
