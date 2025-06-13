/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:25:03 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 19:40:05 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_command_child(t_shell *shell, t_ast *ast)
{
	char	**env_array;
	char	*command_path;

	setup_child_signals();
	if (!ast || !ast->value)
		exit(127);
	if (!ast->args || !ast->args[0])
		exit(127);
	env_array = env_to_array(shell->env);
	if (!env_array)
		exit(127);
	command_path = find_command_path(shell, ast->args[0]);
	if (!command_path)
	{
		print_error(true, ast->args[0], NULL, "command not found\n");
		free_env_array(env_array);
		gc_cleanup(shell->gc);
		cleanup_shell(shell);
		exit(127);
	}
	execve(command_path, ast->args, env_array);
	perror("minishell: execve");
	free(command_path);
	free_env_array(env_array);
	exit(127);
}

int	execute_command_extern(t_shell *shell, t_ast *ast, bool child_process)
{
	pid_t	pid;

	if (!ast || !ast->value)
		return (ERROR);
	if (child_process)
	{
		execute_command_child(shell, ast);
		return (SUCCESS);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (ERROR);
	}
	if (pid == 0)
		return (execute_command_child(shell, ast));
	else
		return (handle_parent_process(shell, pid));
	return (SUCCESS);
}

int	execute_command(t_shell *shell, t_ast *ast, bool child_process)
{
	if (!shell || !ast)
		return (ERROR);
	if (ast->type == TOKEN_BUILTIN)
		return (execute_builtin(shell, ast));
	if (child_process)
	{
		return (execute_command_child(shell, ast));
	}
	else
	{
		return (execute_command_extern(shell, ast, child_process));
	}
}
