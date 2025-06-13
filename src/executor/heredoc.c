/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:47:28 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 18:39:32 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_heredoc_redirection(t_shell *shell, int read_fd)
{
	int	saved_stdin;

	saved_stdin = save_descriptor(STDIN_FILENO);
	if (saved_stdin == -1)
		return (ERROR);
	if (gc_add_fd(shell->gc, saved_stdin) == ERROR)
	{
		close(saved_stdin);
		return (ERROR);
	}
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		restore_descriptor(saved_stdin, STDIN_FILENO);
		return (ERROR);
	}
	close(read_fd);
	return (saved_stdin);
}

int	execute_with_heredoc(t_shell *shell, t_ast *ast, int read_fd)
{
	int	result;
	int	saved_stdin;

	saved_stdin = setup_heredoc_redirection(shell, read_fd);
	if (saved_stdin == ERROR)
		return (ERROR);
	result = execute_ast(shell, ast, false);
	restore_descriptor(saved_stdin, STDIN_FILENO);
	return (result);
}

int	process_heredocs_loop(t_shell *shell, char **delimiters, int count)
{
	int	final_fd;
	int	temp_fd;
	int	i;

	final_fd = -1;
	i = 0;
	while (i < count)
	{
		temp_fd = process_single_heredoc(shell, delimiters[i]);
		if (temp_fd == -1)
		{
			if (final_fd != -1)
				close(final_fd);
			return (-1);
		}
		if (final_fd != -1)
			close(final_fd);
		final_fd = temp_fd;
		i++;
	}
	return (final_fd);
}

int	execute_heredoc(t_shell *shell, t_ast *ast)
{
	char	**delimiters;
	int		delimiter_count;
	int		final_fd;
	t_ast	*final_command;
	int		result;

	delimiters = collect_heredoc_delimiters(shell, ast, &delimiter_count);
	if (!delimiters)
		return (ERROR);
	final_fd = process_heredocs_loop(shell, delimiters, delimiter_count);
	if (final_fd == -1)
		return (SUCCESS);
	final_command = find_command_after_heredocs(ast);
	if (!final_command)
	{
		if (final_fd != -1)
			save_close(&final_fd);
		return (SUCCESS);
	}
	result = execute_with_heredoc(shell, final_command, final_fd);
	return (result);
}
