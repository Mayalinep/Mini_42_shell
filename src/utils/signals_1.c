/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:54:01 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/10 20:31:57 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigsegv(int sig)
{
	(void)sig;
	ft_putstr_fd("Segmentation fault\n", STDERR_FILENO);
	exit(128 + SIGSEGV);
}

static void	handle_sigabrt(int sig)
{
	(void)sig;
	ft_putstr_fd("Abort\n", STDERR_FILENO);
	exit(128 + SIGABRT);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_signal_pid != 0)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	signal(SIGSEGV, handle_sigsegv);
	signal(SIGABRT, handle_sigabrt);
}
