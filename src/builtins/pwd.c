/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 00:01:17 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/09 00:01:27 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *shell, t_ast *ast)
{
	char	*path;

	path = NULL;
	if (ast)
	{
		if (ast->value[0] == '-' && (ft_strncmp(ast->value, "-", 2)
				|| ft_strncmp(ast->value, "--", 3)))
		{
			error_invalid_option("pwd", ast->value, "pwd [-LP]");
			return (shell->exit_status = 1, ERROR);
		}
	}
	if (!save_getcwd(&path, "pwd"))
		return (shell->exit_status = 1, ERROR);
	if (!path)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n",
			STDERR_FILENO);
		return (shell->exit_status = 1, ERROR);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
