/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:42 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:44 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

char	*gc_strdup(t_gc *gc, const char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	dup = gc_malloc(gc, sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
