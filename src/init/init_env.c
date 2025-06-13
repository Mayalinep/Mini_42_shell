/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:51:38 by mpelage           #+#    #+#             */
/*   Updated: 2025/05/27 16:51:40 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_empty_env(t_shell *shell)
{
	t_env	*new_node;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ERROR);
	new_node = create_env_node("PWD");
	if (!new_node)
	{
		free(pwd);
		return (ERROR);
	}
	free(new_node->value);
	new_node->value = pwd;
	add_env_node(&shell->env, new_node);
	return (SUCCESS);
}

int	init_env(t_shell *shell, char **env)
{
	t_env	*new_node;
	int		i;

	if (!shell)
		return (ERROR);
	shell->env = NULL;
	if (!env || !*env)
		return (init_empty_env(shell));
	i = 0;
	while (env[i])
	{
		new_node = create_env_node(env[i]);
		if (!new_node)
		{
			free_env(shell->env);
			return (ERROR);
		}
		add_env_node(&shell->env, new_node);
		i++;
	}
	return (SUCCESS);
}
