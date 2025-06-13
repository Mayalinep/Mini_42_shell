/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:03:40 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 20:47:21 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	apply_single_redirection(t_shell *shell, t_ast *ast)
{
	int	fd;

	if (ast->type == TOKEN_REDIR_IN)
	{
		fd = open_input_file(shell, ast);
		if (fd == -1)
			return (ERROR);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (ast->type == TOKEN_REDIR_OUT || ast->type == TOKEN_APPEND)
	{
		fd = open_output_file(shell, ast);
		if (fd == -1)
			return (ERROR);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ast->type == TOKEN_HEREDOC)
	{
		if (apply_redir_heredocs(shell, ast) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	apply_redirections_recursive(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return (SUCCESS);
	if (ast->type == TOKEN_REDIR_IN || ast->type == TOKEN_REDIR_OUT
		|| ast->type == TOKEN_APPEND || ast->type == TOKEN_HEREDOC)
	{
		if (ast->left && apply_redirections_recursive(shell,
				ast->left) == ERROR)
			return (ERROR);
		return (apply_single_redirection(shell, ast));
	}
	return (SUCCESS);
}

static t_ast	*find_final_command(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->type == TOKEN_REDIR_IN || ast->type == TOKEN_REDIR_OUT
		|| ast->type == TOKEN_APPEND || ast->type == TOKEN_HEREDOC)
	{
		return (find_final_command(ast->left));
	}
	if (ast->type == TOKEN_COMMAND || ast->type == TOKEN_BUILTIN)
		return (ast);
	return (NULL);
}

int	execute_multiple_redirections(t_shell *shell, t_ast *ast)
{
	t_saved_fds	saved;
	t_ast		*final_command;
	int			result;

	ft_memset(&saved, -1, sizeof(t_saved_fds));
	if (save_all_descriptors(&saved) == ERROR)
		return (ERROR);
	if (apply_redirections_recursive(shell, ast) == ERROR)
	{
		restore_all_descriptors(&saved);
		return (ERROR);
	}
	final_command = find_final_command(ast);
	if (final_command)
		result = execute_ast(shell, final_command, false);
	else
		result = SUCCESS;
	restore_all_descriptors(&saved);
	return (result);
}

int	execute_redirection(t_shell *shell, t_ast *ast)
{
	return (execute_multiple_redirections(shell, ast));
}
