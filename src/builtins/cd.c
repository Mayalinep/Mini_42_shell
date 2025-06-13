/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:45:24 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 02:55:30 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(char *oldpath, t_shell *shell)
{
	char	*new_path;

	new_path = NULL;
	if (!save_getcwd(&new_path, "cd"))
	{
		free(oldpath);
		return (shell->exit_status = 1, ERROR);
	}
	if (!set_env_value(&shell->env, "PWD", new_path))
	{
		free(new_path);
		return (shell->exit_status = 1, ERROR);
	}
	if (!set_env_value(&shell->env, "OLDPWD", oldpath))
	{
		free(new_path);
		return (shell->exit_status = 1, ERROR);
	}
	free(oldpath);
	free(new_path);
	return (shell->exit_status = 0, SUCCESS);
}

int	change_directory(char *old_pwd, char *path)
{
	(void)old_pwd;
	if (save_access(path, F_OK, "cd"))
	{
		if (chdir(path) != 0)
		{
			print_errno("cd", path, -1);
			return (ERROR);
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int	builtin_cd(t_shell *shell, t_ast *ast)
{
	char	*path;
	char	*old_pwd;

	old_pwd = NULL;
	if (!ast)
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
			return (print_error(false, "cd", NULL, "HOME not set\n"),
				shell->exit_status = 1, ERROR);
	}
	else if (ast->next)
		return (print_error(true, "cd", NULL, "too many arguments\n"),
			shell->exit_status = 1, ERROR);
	else
		path = ast->value;
	if (path == NULL)
		return (print_error(false, "cd", NULL, "path is NULL\n"),
			shell->exit_status = 1, ERROR);
	if (save_getcwd(&old_pwd, "cd") && change_directory(old_pwd, path))
		return (update_pwd(old_pwd, shell));
	else
		return (free(old_pwd), shell->exit_status = 1, ERROR);
}
