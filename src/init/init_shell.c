/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:50 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/07 10:48:20 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_shell(t_shell *shell, char **env)
{
	if (!shell)
		return (ERROR);
	shell->token_list = NULL;
	shell->input = NULL;
	shell->exit_status = 0;
	shell->is_running = 1;
	shell->signal_status = 0;
	shell->quotes.in_single_quote = 0;
	shell->quotes.in_double_quote = 0;
	g_signal_pid = 0;
	if (init_env(shell, env) == ERROR)
	{
		free(shell->input);
		return (ERROR);
	}
	signals();
	return (SUCCESS);
}
