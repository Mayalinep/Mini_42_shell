/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:25:48 by mpelage           #+#    #+#             */
/*   Updated: 2025/03/10 15:36:46 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **tab, int count)
{
	while (count > 0)
	{
		count--;
		free(tab[count]);
	}
	free(tab);
}

static int	count_slices(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++count;
		while (*s && *s != sep)
			++s;
	}
	return (count);
}

static char	*create_slice(const char *s, size_t len)
{
	char	*slice;

	slice = ft_substr(s, 0, len);
	return (slice);
}

static int	fill_slices(char **tab, char const *s, char sep)
{
	int			count;
	char const	*start;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != sep)
				s++;
			tab[count] = create_slice(start, s - start);
			if (!tab[count])
				return (count);
			count++;
		}
	}
	return (-1);
}

char	**ft_split(char const *s, char sep)
{
	char	**res;
	int		slice_count;
	int		error_index;

	if (!s)
		return (NULL);
	slice_count = count_slices(s, sep);
	res = (char **)malloc((slice_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	error_index = fill_slices(res, s, sep);
	if (error_index >= 0)
	{
		free_split(res, error_index);
		return (NULL);
	}
	res[slice_count] = NULL;
	return (res);
}
