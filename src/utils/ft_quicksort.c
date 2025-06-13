/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 00:03:39 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 00:04:13 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env_ptrs(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(t_env *arr[], int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = arr[high]->key;
	i = (low - 1);
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j]->key, pivot) < 0)
		{
			i++;
			swap_env_ptrs(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_env_ptrs(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	ft_quicksort(t_env *arr[], int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		ft_quicksort(arr, low, pi - 1);
		ft_quicksort(arr, pi + 1, high);
	}
}

t_env	**create_arr_list(t_env *env, t_gc *gc)
{
	t_env	**env_array;
	t_env	*current;
	int		count;
	int		i;

	count = count_env_vars(env);
	if (count == 0)
		return (NULL);
	env_array = (t_env **)gc_malloc(gc, sizeof(t_env *) * count);
	if (!env_array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		env_array[i++] = current;
		current = current->next;
	}
	return (env_array);
}
