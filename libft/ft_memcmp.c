/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:58:25 by mpelage           #+#    #+#             */
/*   Updated: 2024/05/25 12:44:30 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n && ptr1[i] == ptr2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n);

int	main(void)
{
	char	str1[] = "Hello, world!";
	char	str2[] = "Hello, world!";
	char	str3[] = "Hello, 42!";
	size_t	len;

	// Test 1 : Les chaînes sont identiques
	len = strlen(str1);
	printf("Test 1 - ft_memcmp(str1, str2, %zu) = %d\n", len, ft_memcmp(str1,
			str2, len));
	// Test 2 : Les chaînes sont différentes
	printf("Test 2 - ft_memcmp(str1, str3, %zu) = %d\n", len, ft_memcmp(str1,
			str3, len));
	// Test 3 : Comparaison partielle
	len = 7;
	printf("Test 3 - ft_memcmp(str1, str3, %zu) = %d\n", len, ft_memcmp(str1,
			str3, len));
	return (0);
}
*/
