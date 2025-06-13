/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:10 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:59:29 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	gc_cleanup(t_gc *gc)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!gc)
		return ;
	current = gc->head;
	while (current)
	{
		next = current->next;
		if (current->type == GC_MEM && current->p)
			free(current->p);
		else if (current->type == GC_FD)
		{
			if (current->fd >= 0)
				close(current->fd);
			if (current->heredoc_fd[0] >= 0)
				close(current->heredoc_fd[0]);
			if (current->heredoc_fd[1] >= 0)
				close(current->heredoc_fd[1]);
		}
		free(current);
		current = next;
	}
	gc->head = NULL;
}

void	gc_fclean(t_gc *gc)
{
	if (!gc)
		return ;
	gc_cleanup(gc);
	free(gc);
}
