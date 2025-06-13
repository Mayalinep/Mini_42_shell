/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:44:29 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 20:44:31 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*build_builtin_node(t_gc *gc, t_token **tokens, t_ast *node)
{
	t_token	*current;

	current = *tokens;
	if (!current || current->type != TOKEN_WORD)
	{
		return (NULL);
	}
	if (!node)
	{
		node = create_ast_node(gc, TOKEN_BUILTIN, current->value);
		if (!node)
			return (NULL);
		current = current->next;
	}
	while (current && current->type == TOKEN_WORD)
	{
		add_builtin_arg(gc, node, current->value);
		current = current->next;
	}
	*tokens = current;
	return (node);
}

t_ast	*build_command_node(t_gc *gc, t_token **tokens, t_ast *node)
{
	t_token	*current;

	current = *tokens;
	if (!current || current->type != TOKEN_WORD)
	{
		return (NULL);
	}
	if (!node || !node->value)
	{
		node = create_ast_node(gc, TOKEN_COMMAND, current->value);
		if (!node)
			return (NULL);
	}
	while (current && current->type == TOKEN_WORD)
	{
		add_command_arg(gc, node, current->value);
		current = current->next;
	}
	*tokens = current;
	return (node);
}

t_ast	*build_ast_recursive(t_gc *gc, t_token **tokens)
{
	return (parse_logical_op(gc, tokens));
}

t_ast	*build_ast(t_shell *shell)
{
	t_token	*current;

	current = shell->token_list;
	return (build_ast_recursive(shell->gc, &current));
}
