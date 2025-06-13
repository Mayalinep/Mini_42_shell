/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:17 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 01:51:13 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_double_operators(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (TOKEN_APPEND);
	if (!ft_strncmp(str, "&&", 2))
		return (TOKEN_AND);
	if (!ft_strncmp(str, "||", 2))
		return (TOKEN_OR);
	return (0);
}

static int	check_single_operators(char *str)
{
	if (!ft_strncmp(str, "<", 1))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(str, ">", 1))
		return (TOKEN_REDIR_OUT);
	if (!ft_strncmp(str, "|", 1))
		return (TOKEN_PIPE);
	if (!ft_strncmp(str, "&", 1))
		return (TOKEN_BACKGROUND);
	if (!ft_strncmp(str, "(", 1))
		return (TOKEN_PAREN_OPEN);
	if (!ft_strncmp(str, ")", 1))
		return (TOKEN_PAREN_CLOSE);
	return (0);
}

int	is_special(char *str, char *original_cmd, int position)
{
	int	result;
	int	len;

	if (!str || !*str || get_quote_type_at_position(original_cmd,
			position) != 0)
		return (0);
	len = ft_strlen(str);
	if (len >= 2)
	{
		result = check_double_operators(str);
		if (result)
			return (result);
	}
	if (len >= 1)
	{
		result = check_single_operators(str);
		if (result)
			return (result);
	}
	return (0);
}

int	check_token_syntax_error(char *str)
{
	if (!str || !*str)
		return (ERROR);
	if (str[0] == '|' && str[1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (ERROR);
	}
	if (str[0] == '>' && str[1] == '>' && str[2] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (ERROR);
	}
	if (str[0] == '<' && str[1] == '<' && str[2] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		return (ERROR);
	}
	if (str[0] == '&' && str[1] == '&')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int	get_quote_type(char *value)
{
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		return (2);
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (1);
	return (0);
}
