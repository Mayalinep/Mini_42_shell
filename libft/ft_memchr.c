/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:54:38 by mpelage           #+#    #+#             */
/*   Updated: 2024/06/02 15:43:06 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	cc;

	ptr = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == cc)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Hello, world!";
	char	ch;
	void	*result;
	size_t	len;

	// Cas 1 : caractère présent
	ch = 'o';
	len = strlen(str);
	result = ft_memchr(str, ch, len);
	if (result != NULL)
		printf("Le caractère '%c' a été trouvé à la position : %ld\n", ch,
			(char *)result - str);
	else
		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n", ch);
	// Cas 2 : caractère absent
	ch = 'x';
	result = ft_memchr(str, ch, len);
	if (result != NULL)
		printf("Le caractère '%c' a été trouvé à la position : %ld\n", ch,
			(char *)result - str);
	else
		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n", ch);
	// Cas 3 : recherche limitée
	ch = 'o';
	len = 5;
	result = ft_memchr(str, ch, len);
	if (result != NULL)
		printf("Le caractère '%c' a été trouvé dans les
			%ld premiers caractères à la position : %ld\n", ch, len,
			(char *)result - str);
	else
		printf("Le caractère '%c' n'a pas été trouvé dans les
			%ld premiers caractères.\n", ch, len);
	return (0);
}
*/
