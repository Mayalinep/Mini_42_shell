/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:24:03 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 10:24:05 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *shell, t_ast *ast)
{
	t_ast	*cur;

	cur = ast;
	while (cur)
	{
		if (get_env_value(shell->env, cur->value))
		{
			remove_env_var(&shell->env, cur->value);
		}
		else
		cur = cur->next;
	}
	shell->exit_status = 0;
	return (SUCCESS);
}
