/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:54:01 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 20:32:13 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	handle_heredoc_signals(int status, t_shell *shell, int pipe_fd)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		close(pipe_fd);
		shell->exit_status = 128 + WTERMSIG(status);
		return (-1);
	}
	return (pipe_fd);
}

int	handle_parent_process(t_shell *shell, pid_t pid)
{
	int	status;

	if (pid <= 0)
	{
		perror("minishell: fork");
		return (ERROR);
	}
	g_signal_pid = pid;
	waitpid(pid, &status, 0);
	g_signal_pid = 0;
	return (handle_child_exit(status, shell));
}
