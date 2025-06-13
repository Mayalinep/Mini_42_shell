/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:34 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:59:40 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_redir	*gc_add_redirection(t_gc *gc, int original_fd, int new_fd)
{
	t_redir		*redir;
	t_gc_node	*node;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->original_fd = original_fd;
	redir->new_fd = new_fd;
	redir->saved_fd = save_descriptor(original_fd);
	if (redir->saved_fd == -1)
	{
		free(redir);
		return (NULL);
	}
	node = gc_create_node(NULL, -1, GC_FD);
	if (!node)
	{
		close(redir->saved_fd);
		free(redir);
		return (NULL);
	}
	node->redir = redir;
	node->next = gc->head;
	gc->head = node;
	return (redir);
}

int	gc_apply_redirection(t_redir *redir)
{
	if (redir->saved_fd == -1)
		redir->saved_fd = dup(redir->original_fd);
	if (dup2(redir->new_fd, redir->original_fd) == -1)
		return (ERROR);
	close(redir->new_fd);
	redir->new_fd = -1;
	return (SUCCESS);
}

void	gc_restore_redirection(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->saved_fd != -1)
	{
		dup2(redir->saved_fd, redir->original_fd);
		close(redir->saved_fd);
	}
	if (redir->new_fd != -1)
		close(redir->new_fd);
}
