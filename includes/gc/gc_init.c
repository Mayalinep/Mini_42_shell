/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:17 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:19 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	return (gc);
}

t_gc_node	*gc_create_node(void *ptr, int fd, t_gc_type type)
{
	t_gc_node	*new_node;

	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return (NULL);
	new_node->p = ptr;
	new_node->fd = fd;
	new_node->heredoc_fd[0] = -1;
	new_node->heredoc_fd[1] = -1;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}
