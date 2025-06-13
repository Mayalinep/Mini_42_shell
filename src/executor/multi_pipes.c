/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:58:53 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 21:56:57 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_left_multi_child(t_shell *shell, t_ast *ast, t_pipe_data *data)
{
	int	result;

	close(data->pipe_fd[0]);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	close(data->pipe_fd[1]);
	if (ast->left->type == TOKEN_PIPE)
		result = execute_multiple_pipes(shell, ast->left);
	else
		result = execute_ast(shell, ast->left, true);
	gc_cleanup(shell->gc);
	cleanup_shell(shell);
	if (result == SUCCESS)
		exit(0);
	exit(1);
}

static void	exec_right_multi_child(t_shell *shell, t_ast *ast,
		t_pipe_data *data)
{
	int	result;

	close(data->pipe_fd[1]);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	close(data->pipe_fd[0]);
	if (ast->right->type == TOKEN_PIPE)
		result = execute_multiple_pipes(shell, ast->right);
	else
		result = execute_ast(shell, ast->right, true);
	gc_cleanup(shell->gc);
	cleanup_shell(shell);
	if (result == SUCCESS)
		exit(0);
	exit(1);
}

int	execute_multiple_pipes(t_shell *shell, t_ast *ast)
{
	t_pipe_data	data;

	if (ast->type != TOKEN_PIPE)
		return (execute_ast(shell, ast, false));
	if (ast->left->type != TOKEN_PIPE && ast->right->type != TOKEN_PIPE)
		return (execute_pipeline(shell, ast));
	if (pipe(data.pipe_fd) == -1)
		return (perror("minishell: pipe"), handle_exit_status(shell, ERROR));
	data.pid_left = safe_fork(shell);
	if (data.pid_left == -1)
		return (handle_fork_error(&data));
	if (data.pid_left == 0)
		exec_left_multi_child(shell, ast, &data);
	data.pid_right = safe_fork(shell);
	if (data.pid_right == -1)
		return (handle_fork_error(&data));
	if (data.pid_right == 0)
		exec_right_multi_child(shell, ast, &data);
	save_close_pipe_fds(&data);
	waitpid(data.pid_left, NULL, 0);
	waitpid(data.pid_right, &data.status, 0);
	return (handle_child_exit(data.status, shell));
}

int	execute_pipe(t_shell *shell, t_ast *ast)
{
	if (!ast || ast->type != TOKEN_PIPE)
		return (ERROR);
	return (execute_multiple_pipes(shell, ast));
}
