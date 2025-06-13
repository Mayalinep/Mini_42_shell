/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:14:25 by maya              #+#    #+#             */
/*   Updated: 2024/06/02 15:34:32 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr;
	const char	*sptr;

	if (!dst && !src)
		return (NULL);
	ptr = (char *)dst;
	sptr = (const char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = sptr[i];
		i++;
	}
	return (dst);
}
