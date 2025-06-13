/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:59:51 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:59:55 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "libft.h"
# include <limits.h>
# include <stdint.h>
# include <stdio.h>

# define SUCCESS 1
# define ERROR 0
# define ERROR_SYNTAX 2

typedef enum e_gc_type
{
	GC_MEM,
	GC_FD
}						t_gc_type;

// Structure locale pour la redirection
typedef struct s_redir
{
	int					original_fd;
	int					new_fd;
	int					saved_fd;
}						t_redir;

typedef struct s_gc_node
{
	void				*p;
	int					fd;
	int					heredoc_fd[2];
	t_gc_type			type;
	t_redir				*redir;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc
{
	t_gc_node			*head;
}						t_gc;

/* Fonctions d'initialisation */
t_gc					*gc_init(void);

/* Fonctions d'allocation */
void					*gc_malloc(t_gc *gc, size_t size);
void					*gc_calloc(t_gc *gc, size_t count, size_t size);
char					*gc_strdup(t_gc *gc, const char *s);
char					*gc_strjoin(t_gc *gc, const char *s1, const char *s2);
char					*gc_substr(t_gc *gc, const char *s, unsigned int start,
							size_t len);

/* Fonctions d'ajout au GC */
int						gc_add_ptr(t_gc *gc, void *ptr);
int						gc_add_fd(t_gc *gc, int fd);
int						gc_add_heredoc(t_gc *gc, int read_fd, int write_fd);

/*Fonctions GC pour redirections*/
t_redir					*gc_add_redirection(t_gc *gc, int original_fd,
							int new_fd);
int						gc_apply_redirection(t_redir *redir);
void					gc_restore_redirection(t_redir *redir);
int						save_descriptor(int fd);

/* Fonctions de nettoyage */
void					gc_fclean(t_gc *gc);
void					gc_cleanup(t_gc *gc);
t_gc_node				*gc_create_node(void *ptr, int fd, t_gc_type type);

#endif