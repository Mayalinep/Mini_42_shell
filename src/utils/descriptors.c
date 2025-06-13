/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:21:03 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:05:37 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	restore_descriptor(int saved_fd, int target_fd)
{
	if (saved_fd == -1)
		return (SUCCESS);
	if (dup2(saved_fd, target_fd) == -1)
	{
		perror("minishell: dup2");
		return (ERROR);
	}
	close(saved_fd);
	return (SUCCESS);
}

int	open_input_file(t_shell *shell, t_ast *ast)
{
	int	fd;

	fd = open(ast->right->value, O_RDONLY);
	if (fd == -1)
	{
		shell->exit_status = 1;
		perror("minishell");
		return (-1);
	}
	return (fd);
}

int	open_output_file(t_shell *shell, t_ast *ast)
{
	int	fd;

	if (ast->type == TOKEN_REDIR_OUT)
		fd = open(ast->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(ast->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->exit_status = 1;
		print_errno("minishell", ast->right->value, errno);
		return (-1);
	}
	return (fd);
}

int	save_all_descriptors(t_saved_fds *saved)
{
	saved->saved_stdin = save_descriptor(STDIN_FILENO);
	saved->saved_stdout = save_descriptor(STDOUT_FILENO);
	saved->saved_stderr = save_descriptor(STDERR_FILENO);
	if (saved->saved_stdin == -1 || saved->saved_stdout == -1
		|| saved->saved_stderr == -1)
		return (ERROR);
	return (SUCCESS);
}

int	restore_all_descriptors(t_saved_fds *saved)
{
	int	result;

	result = SUCCESS;
	if (saved->saved_stdin != -1)
	{
		if (restore_descriptor(saved->saved_stdin, STDIN_FILENO) == ERROR)
			result = ERROR;
	}
	if (saved->saved_stdout != -1)
	{
		if (restore_descriptor(saved->saved_stdout, STDOUT_FILENO) == ERROR)
			result = ERROR;
	}
	if (saved->saved_stderr != -1)
	{
		if (restore_descriptor(saved->saved_stderr, STDERR_FILENO) == ERROR)
			result = ERROR;
	}
	return (result);
}
