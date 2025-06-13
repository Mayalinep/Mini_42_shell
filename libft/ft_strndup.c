/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:45:31 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 00:07:40 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(char *str, size_t n)
{
	char	*new_str;
	size_t	i;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < n && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
