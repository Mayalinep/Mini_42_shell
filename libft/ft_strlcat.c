/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 06:59:02 by maya              #+#    #+#             */
/*   Updated: 2024/06/02 15:37:14 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	initial_len;

	i = 0;
	j = 0;
	while (dest[i] != '\0' && i < len)
		i++;
	initial_len = i;
	if (len == 0)
		return (initial_len + ft_strlen(src));
	while (src[j] != '\0' && i < len - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (i < len)
		dest[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (initial_len + j);
}
