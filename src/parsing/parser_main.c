/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:39 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 01:43:54 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_token_list(t_shell *shell)
{
	shell->token_list = NULL;
	return (SUCCESS);
}

int	check_control_operators(t_token *token_list)
{
	t_token	*current;

	if (!token_list)
		return (SUCCESS);
	if (token_list->type == TOKEN_PIPE)
		return (print_token_error(token_list->type));
	current = token_list;
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return (print_token_error(current->type));
	return (SUCCESS);
}

static int	check_control(t_shell *shell, t_token *token_list)
{
	if (check_control_operators(token_list) == ERROR)
	{
		shell->exit_status = 2;
		return (ERROR);
	}
	else if (check_parentheses(token_list) == ERROR)
	{
		shell->exit_status = 2;
		return (ERROR);
	}
	else if (check_redirections(token_list) == ERROR)
	{
		shell->exit_status = 2;
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_command(t_shell *shell)
{
	if (check_unclosed_quotes(shell->input) == ERROR)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n",
			STDERR_FILENO);
		shell->exit_status = 2;
		return (ERROR);
	}
	init_token_list(shell);
	if (expand_variables(shell, &shell->input) == ERROR)
		return (ERROR);
	if (tokenize_command(shell, shell->input, shell->input) == ERROR)
	{
		free_tokens(shell->token_list);
		return (ERROR);
	}
	if (check_control(shell, shell->token_list) == ERROR)
	{
		free_tokens(shell->token_list);
		return (ERROR);
	}
	return (SUCCESS);
}
