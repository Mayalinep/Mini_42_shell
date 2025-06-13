/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:29:39 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 20:32:17 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit_status(t_shell *shell, int status)
{
	if (!shell)
	{
		ft_putstr_fd("Error: shell is NULL\n", STDERR_FILENO);
		return (ERROR);
	}
	shell->exit_status = 1;
	return (status);
}

int	handle_child_exit(int status, t_shell *shell)
{
	int	sig;

	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->exit_status = 128 + sig;
		if (sig == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	return (SUCCESS);
}
