/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:47:31 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 23:33:28 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell, t_ast *ast)
{
	t_env	*env;

	if (ast)
	{
		print_error(false, "env", NULL, "too many arguments\n");
		return (shell->exit_status = 1, ERROR);
	}
	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env = env->next;
	}
	shell->exit_status = 0;
	return (SUCCESS);
}
