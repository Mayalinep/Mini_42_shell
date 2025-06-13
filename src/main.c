/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:46:33 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/10 20:50:23 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal_pid = 0;

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input != NULL)
		free(shell->input);
	if (shell->token_list)
		free_tokens(shell->token_list);
	if (shell->env)
		free_env(shell->env);
	if (shell->gc)
	{
		gc_cleanup(shell->gc);
		free(shell->gc);
	}
}

static int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (i == (int)ft_strlen(line))
		return (SUCCESS);
	return (ERROR);
}

static int	handle_input_and_validation(t_shell *shell)
{
	shell->input = readline(PROMPT);
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->input = NULL;
		return (0);
	}
	if (empty_line(shell->input) == SUCCESS)
	{
		shell->input = free_s(shell->input);
		return (1);
	}
	add_history(shell->input);
	return (2);
}

static void	shell_loop(t_shell *shell)
{
	int	status;

	while (shell->is_running)
	{
		status = handle_input_and_validation(shell);
		if (status == 0)
			break ;
		if (status == 1)
			continue ;
		if (parse_command(shell) == SUCCESS)
		{
			if (execute_shell(shell) == ERROR)
				if (shell->exit_status == 0)
					shell->exit_status = 1;
			free_tokens(shell->token_list);
			shell->token_list = NULL;
		}
		else
		{
			cleanup_tokens_only(shell);
		}
		cleanup_tokens_only(shell);
		shell->input = free_s(shell->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, env) == ERROR)
		return (ERROR);
	signals();
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.exit_status);
}
