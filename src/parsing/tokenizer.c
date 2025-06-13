/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:27 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 01:52:10 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	length_cmd(char *command, int *quotes, char *original_cmd,
		int start_pos)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (command[i] && !ft_isspace(command[i]) && !is_special(command + i,
			original_cmd, start_pos + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quotes)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\''
			&& !ft_isspace(command[i]) && !is_special(command + i, original_cmd,
				start_pos + i))
			++i;
	}
	return (i);
}

static int	create_word_token(t_shell *shell, char **command,
		char *original_cmd, int start_pos)
{
	char	*str;
	int		length;
	int		quotes;

	length = length_cmd(*command, &quotes, original_cmd, start_pos);
	if (((length) - (2 * quotes)) < 0)
		return (ERROR);
	str = malloc(sizeof(char) * ((length + 1) - (2 * quotes)));
	if (!str)
		return (ERROR);
	copy_token(*command, length, str);
	if (!append_token(&shell->token_list, str, TOKEN_WORD))
	{
		free(str);
		return (ERROR);
	}
	*command += length;
	return (SUCCESS);
}

static int	create_special_token(t_shell *shell, char **command,
		char *original_cmd, int pos)
{
	int		type;
	char	*special;
	int		len;

	type = is_special(*command, original_cmd, pos);
	if (!type)
		return (ERROR);
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND || type == TOKEN_AND
		|| type == TOKEN_OR)
		len = 2;
	else
		len = 1;
	special = ft_strndup(*command, len);
	if (!special)
		return (ERROR);
	if (!append_token(&shell->token_list, special, type))
	{
		free(special);
		return (ERROR);
	}
	*command += len;
	return (SUCCESS);
}

static int	handle_token_creation(t_shell *shell, char **command,
		char *original_cmd, int pos)
{
	if (is_special(*command, original_cmd, pos))
	{
		if (create_special_token(shell, command, original_cmd, pos) == ERROR)
			return (ERROR);
	}
	else if (create_word_token(shell, command, original_cmd, pos) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	tokenize_command(t_shell *shell, char *command, char *original_cmd)
{
	int	pos;

	pos = 0;
	while (*command)
	{
		while (*command && ft_isspace(*command))
		{
			command++;
			pos++;
		}
		if (!*command)
			break ;
		if (!check_token_syntax_error(command))
		{
			shell->exit_status = 2;
			return (ERROR);
		}
		if (handle_token_creation(shell, &command, original_cmd, pos) == ERROR)
		{
			free_tokens(shell->token_list);
			return (ERROR);
		}
		pos = command - original_cmd;
	}
	return (SUCCESS);
}
