/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:24 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:26 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc_calloc(t_gc *gc, size_t nmemb, size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	if (!gc || !nmemb || !size)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	node = gc_create_node(ptr, -1, GC_MEM);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr || !gc)
		return (NULL);
	node = gc_create_node(ptr, -1, GC_MEM);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}
