/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:36:55 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 20:57:34 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_shell *shell, t_ast *ast)
{
	(void)shell;
	(void)ast;
	if (ft_strncmp(ast->value, "cd", 3) == 0)
		return (builtin_cd(shell, ast->next));
	else if (ft_strncmp(ast->value, "echo", 5) == 0)
		return (builtin_echo(shell, ast->next));
	else if (ft_strncmp(ast->value, "env", 4) == 0)
		return (builtin_env(shell, ast->next));
	else if (ft_strncmp(ast->value, "exit", 5) == 0)
		return (builtin_exit(shell, ast->next));
	else if (ft_strncmp(ast->value, "export", 7) == 0)
		return (builtin_export(shell, ast->next));
	else if (ft_strncmp(ast->value, "pwd", 4) == 0)
		return (builtin_pwd(shell, ast->next));
	else if (ft_strncmp(ast->value, "unset", 6) == 0)
		return (builtin_unset(shell, ast->next));
	return (ERROR);
}

int	execute_ast(t_shell *shell, t_ast *ast, bool child_process)
{
	struct termios	terminal;
	int				res;

	if (!shell || !ast)
		return (ERROR);
	if (!ast)
		return (SUCCESS);
	res = SUCCESS;
	ft_memset(&terminal, 0, sizeof(terminal));
	tcgetattr(STDIN_FILENO, &terminal);
	if (ast->type == TOKEN_COMMAND)
		res = execute_command(shell, ast, child_process);
	else if (ast->type == TOKEN_BUILTIN)
		res = execute_builtin(shell, ast);
	else if (ast->type == TOKEN_HEREDOC)
		res = execute_heredoc(shell, ast);
	else if (is_redir(ast->type))
		res = execute_redirection(shell, ast);
	else if (ast->type == TOKEN_PIPE)
		res = execute_pipeline(shell, ast);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (res);
}

int	execute_shell(t_shell *shell)
{
	int	res;

	if (!shell)
		return (ERROR);
	shell->gc = gc_init();
	if (!shell->gc)
		return (ERROR);
	shell->ast_root = build_ast(shell);
	if (!shell->ast_root)
		return (gc_fclean(shell->gc), ERROR);
	res = execute_ast(shell, shell->ast_root, false);
	gc_fclean(shell->gc);
	shell->gc = NULL;
	shell->ast_root = NULL;
	if (res == ERROR)
	{
		return (ERROR);
	}
	return (res);
}
