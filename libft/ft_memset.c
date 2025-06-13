/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:30:01 by maya              #+#    #+#             */
/*   Updated: 2024/05/28 15:52:46 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	a[] = "Hello";

	write(1, a , 6);
	write(1, "\n",  1);
	ft_memset(a, 'A', 7);
	write(1, a , 7);
	write(1, "\n" ,   1);
	return (0);
}
*/
