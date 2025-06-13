/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:21:55 by mpelage           #+#    #+#             */
/*   Updated: 2024/05/28 15:49:30 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	need;
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	need = count * size;
	ptr = malloc(need);
	if (!ptr)
	{
		return (NULL);
	}
	else
		ft_bzero(ptr, need);
	return (ptr);
}
