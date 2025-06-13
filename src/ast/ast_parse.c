/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:41:29 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 20:42:23 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_command_ast(t_gc *gc, t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	if (!current)
		return (NULL);
	if (current->type == TOKEN_WORD && is_builtins(current->value))
		return (build_builtin_node(gc, tokens, NULL));
	else
		return (build_command_node(gc, tokens, NULL));
}

static t_ast	*process_redirections(t_gc *gc, t_token **tokens, t_ast *left)
{
	t_token	*current;

	current = *tokens;
	while (current && is_redir(current->type))
	{
		left = handle_redirection(gc, tokens, left, current);
		if (!left)
			return (NULL);
		current = *tokens;
	}
	return (left);
}

t_ast	*parse_redirection(t_gc *gc, t_token **tokens)
{
	t_token	*saved_token;
	t_ast	*left;

	saved_token = *tokens;
	left = parse_command_ast(gc, tokens);
	if (!left && saved_token && is_redir(saved_token->type))
	{
		left = create_ast_node(gc, TOKEN_COMMAND, NULL);
		if (!left)
			return (NULL);
		*tokens = saved_token;
	}
	else if (!left)
		return (NULL);
	return (process_redirections(gc, tokens, left));
}

t_ast	*parse_pipeline(t_gc *gc, t_token **tokens)
{
	t_ast	*left_node;
	t_token	*current;

	left_node = parse_redirection(gc, tokens);
	if (!left_node)
		return (NULL);
	current = *tokens;
	if (!current)
		return (left_node);
	if (current->type == TOKEN_PIPE)
		return (handle_pipe_operator(gc, tokens, left_node, current));
	return (left_node);
}

t_ast	*parse_logical_op(t_gc *gc, t_token **tokens)
{
	return (parse_pipeline(gc, tokens));
}
