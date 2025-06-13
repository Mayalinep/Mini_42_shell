/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:50 by mpelage           #+#    #+#             */
/*   Updated: 2024/06/03 19:18:41 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last = (char *)&s[i];
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (last);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello, World!";
	char	ch;
	char	*result;
	char	ch2;
	char	*result2;

	ch = 'o';
	result = ft_strrchr(str, ch);
	if (result)
		printf("Last occurrence of '%c': %s\n", ch, result);
	else
		printf("Character '%c' not found.\n", ch);
	ch2 = 'z';
	result2 = ft_strrchr(str, ch2);
	if (result2)
		printf("Last occurrence of '%c': %s\n", ch2, result2);
	else
		printf("Character '%c' not found.\n", ch2);
	return (0);
}
*/