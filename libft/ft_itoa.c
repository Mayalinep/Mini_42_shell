/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:48:52 by mpelage           #+#    #+#             */
/*   Updated: 2024/06/02 15:49:24 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_res(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	nb;
	char		*res;
	int			len;

	nb = (long int)n;
	len = len_res(nb);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (nb == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	len--;
	while (nb != 0)
	{
		res[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}
