/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:40:15 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 20:45:34 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*handle_word_redirection(t_gc *gc, t_token **tokens, t_ast *left_node)
{
	t_token	*current;

	current = *tokens;
	if (!current)
		return (left_node);
	if (left_node && !left_node->value && current)
		left_node = NULL;
	if (left_node && left_node->type == TOKEN_BUILTIN)
		return (build_builtin_node(gc, tokens, left_node));
	else if (!left_node && current->type == TOKEN_WORD
		&& is_builtins(current->value))
		return (build_builtin_node(gc, tokens, NULL));
	else
		return (build_command_node(gc, tokens, left_node));
}

t_ast	*handle_file_redirection(t_gc *gc, t_token **tokens, t_ast *node)
{
	t_token	*current;

	current = *tokens;
	if (!current || current->type != TOKEN_WORD)
		return (NULL);
	node->right = create_ast_node(gc, TOKEN_FILENAME, current->value);
	if (!node->right)
		return (NULL);
	current = current->next;
	*tokens = current;
	if (current && current->type == TOKEN_WORD)
		node->left = handle_word_redirection(gc, tokens, node->left);
	return (node);
}

t_ast	*handle_heredoc_redirection(t_gc *gc, t_token **tokens, t_ast *node)
{
	t_token	*current;

	current = *tokens;
	if (!current || current->type != TOKEN_WORD)
		return (NULL);
	node->right = create_ast_node(gc, TOKEN_LIMITER, current->value);
	if (!node->right)
		return (NULL);
	current = current->next;
	*tokens = current;
	if (current && current->type == TOKEN_WORD)
		node->left = handle_word_redirection(gc, tokens, node->left);
	return (node);
}

t_ast	*handle_redirection(t_gc *gc, t_token **tokens, t_ast *left_node,
		t_token *current)
{
	t_ast	*node;

	node = create_ast_node(gc, current->type, NULL);
	if (!node)
		return (NULL);
	node->left = left_node;
	*tokens = current->next;
	if (current->type == TOKEN_HEREDOC)
		return (handle_heredoc_redirection(gc, tokens, node));
	else
		return (handle_file_redirection(gc, tokens, node));
}

t_ast	*handle_pipe_operator(t_gc *gc, t_token **tokens, t_ast *left_node,
		t_token *current)
{
	t_ast	*node;

	node = create_ast_node(gc, TOKEN_PIPE, NULL);
	if (!node)
		return (NULL);
	node->left = left_node;
	*tokens = current->next;
	node->right = build_ast_recursive(gc, tokens);
	if (!node->right)
		return (NULL);
	return (node);
}
