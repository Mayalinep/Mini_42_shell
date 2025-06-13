/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:56:43 by mpelage           #+#    #+#             */
/*   Updated: 2024/05/28 15:53:29 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] && little[j] && (i + j) < len
				&& big[i + j] == little[j])
			{
				j++;
			}
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*big = "hello world";
	const char	*little = "world";
	size_t		len;
	char		*result;
	const char	*little2 = "planet";
	const char	*little3 = "";
	const char	*little4 = "hello";
	const char	*little5 = "world";

	len = 11;
	// Test 1: Little trouvé dans Big
	result = ft_strnstr(big, little, len);
	if (result)
		printf("Test 1: Found '%s' in '%s' within %zu characters: %s\n", little,
			big, len, result);
	else
		printf("Test 1: '%s' not found in '%s' within %zu characters.\n",
			little, big, len);
	// Test 2: Little pas trouvé dans Big
	result = ft_strnstr(big, little2, len);
	if (result)
		printf("Test 2: Found '%s' in '%s' within %zu characters: %s\n",
			little2, big, len, result);
	else
		printf("Test 2: '%s' not found in '%s' within %zu characters.\n",
			little2, big, len);
	// Test 3: Little vide
	result = ft_strnstr(big, little3, len);
	if (result)
		printf("Test 3: Found '%s' in '%s' within %zu characters: %s\n",
			little3, big, len, result);
	else
		printf("Test 3: '%s' not found in '%s' within %zu characters.\n",
			little3, big, len);
	// Test 4: Little au début de Big
	result = ft_strnstr(big, little4, len);
	if (result)
		printf("Test 4: Found '%s' in '%s' within %zu characters: %s\n",
			little4, big, len, result);
	else
		printf("Test 4: '%s' not found in '%s' within %zu characters.\n",
			little4, big, len);
	// Test 5: Limite de longueur trop courte
	len = 5;  // Trop court pour trouver "world"
	result = ft_strnstr(big, little5, len);
	if (result)
		printf("Test 5: Found '%s' in '%s' within %zu characters: %s\n",
			little5, big, len, result);
	else
		printf("Test 5: '%s' not found in '%s' within %zu characters.\n",
			little5, big, len);
	return (0);
}
*/
