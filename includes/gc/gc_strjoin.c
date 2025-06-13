/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:50 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/08 23:58:52 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

char	*gc_strjoin(t_gc *gc, const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!gc)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gc_strdup(gc, s2));
	if (!s2)
		return (gc_strdup(gc, s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = gc_malloc(gc, sizeof(char) * (len1 + len2 + 1));
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}
