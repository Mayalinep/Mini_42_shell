/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:00:23 by maya              #+#    #+#             */
/*   Updated: 2024/05/28 15:49:38 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <unistd.h>

void	ft_bzero(void *s, size_t n);

int	main(void) {
	char array[10]; // Déclaration d'un tableau de 10 caractères
	int i = 0;      // Variable pour l'index, utilisée dans les boucles while

	// Initialisation du tableau avec des valeurs non nulles
	while (i < 10) {
		array[i] = 'a' + i; // Assigner 'a', 'b', 'c', ..., 'j' au tableau
		i++;
	}

	// Affichage du tableau avant l'appel à ft_bzero
	printf("Before ft_bzero: ");
	i = 0; // Réinitialiser l'index à 0 pour la nouvelle boucle
	while (i < 10) {
		printf("%c ", array[i]);
		i++;
	}
	printf("\n");

	// Appel de ft_bzero pour mettre à zéro tout le tableau
	ft_bzero(array, 10);

	// Affichage du tableau après l'appel à ft_bzero
	printf("After ft_bzero:  ");
	i = 0; // Réinitialiser l'index à 0 pour la nouvelle boucle
	while (i < 10) {
		printf("%d ", array[i]); //
			%d pour afficher les valeurs entières (attendu: 0)
		i++;
	}
	printf("\n");

	return (0);
}
*/
