/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:17:52 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 10:17:58 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char **args)
{
	int	i;

	if (!ft_isalpha(args[0][0]) && args[0][0] != '_')
	{
		error_invalid_identifier("export", args[0]);
		return (ERROR);
	}
	i = 0;
	while (args[0][++i])
	{
		if (!ft_isalnum(args[0][i]) && args[0][i] != '_')
		{
			if (args[0][i] == '+' && args[0][i + 1] == '\0' && args[1] != NULL)
				return (SUCCESS);
			error_invalid_identifier("export", args[0]);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
