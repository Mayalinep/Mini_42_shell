/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:59:10 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 19:40:49 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	setup_left_pipe(t_pipe_data *data)
{
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		return (ERROR);
	}
	save_close_pipe_fds(data);
	return (SUCCESS);
}

static int	setup_right_pipe(t_pipe_data *data)
{
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return (ERROR);
	}
	save_close_pipe_fds(data);
	return (SUCCESS);
}

static void	exec_left_child(t_shell *shell, t_ast *ast, t_pipe_data *data)
{
	int	result;

	setup_child_signals();
	if (setup_left_pipe(data) == ERROR)
		exit(1);
	result = execute_ast(shell, ast->left, true);
	gc_cleanup(shell->gc);
	cleanup_shell(shell);
	if (result == SUCCESS)
		exit(0);
	exit(1);
}

static void	exec_right_child(t_shell *shell, t_ast *ast, t_pipe_data *data)
{
	int	result;

	setup_child_signals();
	if (setup_right_pipe(data) == ERROR)
		exit(1);
	result = execute_ast(shell, ast->right, true);
	gc_cleanup(shell->gc);
	cleanup_shell(shell);
	if (result == SUCCESS)
		exit(0);
	exit(1);
}

int	execute_pipeline(t_shell *shell, t_ast *ast)
{
	t_pipe_data	data;

	if (!ast || !ast->left || !ast->right)
		return (handle_exit_status(shell, ERROR));
	if (pipe(data.pipe_fd) == -1)
		return (perror("minishell: pipe"), handle_exit_status(shell, ERROR));
	data.pid_left = safe_fork(shell);
	if (data.pid_left == -1)
		return (handle_fork_error(&data));
	if (data.pid_left == 0)
		exec_left_child(shell, ast, &data);
	data.pid_right = safe_fork(shell);
	if (data.pid_right == -1)
		return (handle_fork_error(&data));
	if (data.pid_right == 0)
		exec_right_child(shell, ast, &data);
	save_close_pipe_fds(&data);
	waitpid(data.pid_left, NULL, 0);
	waitpid(data.pid_right, &data.status, 0);
	return (handle_child_exit(data.status, shell));
}
