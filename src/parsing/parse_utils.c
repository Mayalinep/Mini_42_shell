/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:27 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:52:31 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirections(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putstr_fd(get_token_str(current->type), 2);
				ft_putstr_fd("'\n", 2);
				return (ERROR);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	check_parentheses(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == TOKEN_PAREN_OPEN
			|| current->type == TOKEN_PAREN_CLOSE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(get_token_str(current->type), 2);
			ft_putstr_fd("'\n", 2);
			return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
