/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:01 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/10 20:49:31 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour obtenir la chaîne correspondant au type de token
char	*get_token_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("word");
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	if (type == TOKEN_AND)
		return ("&&");
	if (type == TOKEN_OR)
		return ("||");
	if (type == TOKEN_PAREN_OPEN)
		return ("(");
	if (type == TOKEN_PAREN_CLOSE)
		return (")");
	return ("unknown");
}

int	print_token_error(t_token_type type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(get_token_str(type), 2);
	ft_putstr_fd("'\n", 2);
	return (ERROR);
}

void	cleanup_tokens_only(t_shell *shell)
{
	if (shell && shell->token_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
	}
}
