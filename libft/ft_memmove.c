/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:23:39 by maya              #+#    #+#             */
/*   Updated: 2024/05/28 17:54:36 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s = (const char *)src;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	i = 0;
	if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	text[20] = "Example String Text";
	size_t	index;

	printf("Original text: %s\n", text);
	// Test sans chevauchement
	printf("\n--- Test sans chevauchement ---\n");
	index = 0;
	char *source = text + 15;  // Pointeur vers "Text"
	char *destination = text + 8;  // Pointeur vers la position 8
	while (index < 4)
	{
		destination[index] = source[index];
		index++;
	}
	printf("Result after memmove: %s\n", text);
	// Réinitialisation de la chaîne
	strcpy(text, "Example String Text");
		// Remettre la chaîne à son état original
	printf("\nOriginal text reset: %s\n", text);
	// Test avec chevauchement
	printf("\n--- Test avec chevauchement ---\n");
	index = 11;  // Car on va copier 12 caractères
	source = text + 8;  // Pointeur vers la position 8
	destination = text + 7;  // Pointeur vers la position 7
	while (index > 0)
	{
		index--;
		destination[index] = source[index];  // Copie de l'arrière vers l'avant
	}
	printf("Result after memmove with overlap: %s\n", text);
	return (0);
}
*/
