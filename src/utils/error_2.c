/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:33:04 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 16:36:20 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_s(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

int	handle_invalid_arg(t_shell *shell)
{
	print_error(true, "exit", NULL, "numeric argument required");
	shell->is_running = 0;
	shell->exit_status = 2;
	return (ERROR);
}
