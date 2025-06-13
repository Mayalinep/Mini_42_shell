/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:57 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:59 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

char	*gc_substr(t_gc *gc, const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_strdup(gc, ""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = gc_calloc(gc, len + 1, sizeof(char *));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	return (str);
}
