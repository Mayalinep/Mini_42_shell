/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:13:14 by mpelage           #+#    #+#             */
/*   Updated: 2024/05/28 15:49:45 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char *test_cases[] = {
		"12345",      // Test 1: Conversion simple
		"   987",     // Test 2: Conversion avec espaces blancs
		"+123",       // Test 3: Conversion avec signe +
		"-456",       // Test 4: Conversion avec signe -
		"789abc",
			// Test 5: Conversion avec caractères non numériques à la fin
		"",           // Test 6: Conversion d'une chaîne vide
		"    ",       // Test 7: Conversion avec uniquement des espaces blancs
		"++123",      // Test 8: Conversion avec double signe positif
		"--123",      // Test 9: Conversion avec double signe négatif
		"-+123",      // Test 10: Conversion avec signe mixte
		"2147483647", // Test 11: Conversion de l'entier max
		"-2147483648" // Test 12: Conversion de l'entier min
	};
	// Utiliser size_t pour éviter le warning de comparaison de types différents
	for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
	{
		printf("Test %zu: '%s'\n", i + 1, test_cases[i]);
		printf("  atoi    -> %d\n", atoi(test_cases[i]));
		printf("  ft_atoi -> %d\n", ft_atoi(test_cases[i]));
		printf("\n");
	}
	return (0);
}
*/