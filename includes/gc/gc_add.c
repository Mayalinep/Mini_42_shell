/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:04 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:06 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

int	gc_add_heredoc(t_gc *gc, int read_fd, int write_fd)
{
	t_gc_node	*node;

	if (!gc)
		return (ERROR);
	node = gc_create_node(NULL, -1, GC_FD);
	if (!node)
		return (ERROR);
	node->heredoc_fd[0] = read_fd;
	node->heredoc_fd[1] = write_fd;
	node->next = gc->head;
	gc->head = node;
	return (SUCCESS);
}

int	gc_add_fd(t_gc *gc, int fd)
{
	t_gc_node	*node;

	if (!gc || fd < 0)
		return (ERROR);
	node = gc_create_node(NULL, fd, GC_FD);
	if (!node)
		return (ERROR);
	node->fd = fd;
	node->next = gc->head;
	gc->head = node;
	return (SUCCESS);
}

int	gc_add_ptr(t_gc *gc, void *ptr)
{
	t_gc_node	*node;

	if (!gc || !ptr)
		return (ERROR);
	node = gc_create_node(ptr, -1, GC_MEM);
	if (!node)
		return (ERROR);
	node->next = gc->head;
	gc->head = node;
	return (SUCCESS);
}
