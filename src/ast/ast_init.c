/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:40:29 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 20:47:42 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_ast_node(t_gc *gc, t_token_type type, char *value)
{
	t_ast	*node;

	node = gc_malloc(gc, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	if (value != NULL)
		node->value = gc_strdup(gc, value);
	else
		node->value = NULL;
	node->args = NULL;
	node->is_simple = false;
	node->is_double = false;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

t_ast	*ft_last_arg(t_ast *node)
{
	t_ast	*current;

	if (!node || node->type != TOKEN_BUILTIN)
		return (NULL);
	if (!node->next)
		return (node->next);
	current = node->next;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_builtin_arg(t_gc *gc, t_ast *node, char *value)
{
	t_ast	*new_arg;
	t_ast	*last;

	if (!node || node->type != TOKEN_BUILTIN || !value)
	{
		return ;
	}
	new_arg = create_ast_node(gc, TOKEN_ARG, value);
	if (!new_arg)
		return ;
	last = ft_last_arg(node);
	if (!last)
		node->next = new_arg;
	else
		last->next = new_arg;
}

void	add_command_arg(t_gc *gc, t_ast *node, char *value)
{
	int		i;
	int		j;
	char	**new_args;

	if (!node || node->type != TOKEN_COMMAND || !value)
		return ;
	i = 0;
	if (node->args)
		while (node->args[i])
			i++;
	new_args = gc_calloc(gc, (i + 2), sizeof(char *));
	if (!new_args)
		return ;
	j = -1;
	while (++j < i)
		new_args[j] = node->args[j];
	new_args[i] = gc_strdup(gc, value);
	if (!new_args[i])
		return ;
	new_args[i + 1] = NULL;
	node->args = new_args;
}

// void free_arr(char **arr)
// {
// 	int i;

// 	if (!arr)
// 		return ;
// 	i = -1;
// 	while (arr[++i])
// 			free(arr[i]);
// 	free(arr);
// }

// void free_ast(t_ast *node)
// {
// 	int i;

//     if (!node)
//         return ;
// 	if (node->next)
//         free_ast(node->next);
// 	if (node->left)
//         free_ast(node->left);
// 	if (node->right)
//         free_ast(node->right);
// 	if (node->next != NULL)
// 		free_ast(node->next);
//     if (node->args)
// 		free_arr(node->args);
//     if (node->value)
//         free(node->value);
//     free(node);
// }
