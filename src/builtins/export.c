/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:18:05 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:01:04 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_export_arg(t_shell *shell, char **args)
{
	if (!args || !args[0])
		return (ERROR);
	if (ft_strchr(args[0], '+'))
		return (handle_key_arg(shell, args));
	if (is_env_exist(shell->env, args[0]))
	{
		if (!set_env_value(&shell->env, args[0], args[1]))
			return (ERROR);
	}
	else
	{
		if (!set_env_value(&shell->env, args[0], args[1]))
			return (ERROR);
	}
	return (SUCCESS);
}

char	**value_to_args(t_gc *gc, char *value)
{
	char	*equal_pos;

	if (!value)
		return (NULL);
	equal_pos = ft_strchr(value, '=');
	if (equal_pos)
		return (handle_with_equal(gc, value, equal_pos));
	else
		return (handle_no_equal(gc, value));
}

int	display_export_vars(t_shell *shell)
{
	int		i;
	t_env	**env_array;
	int		count;

	env_array = create_arr_list(shell->env, shell->gc);
	if (!env_array)
		return (ft_putstr_fd("export: memory allocation error\n",
				STDERR_FILENO), ERROR);
	i = -1;
	count = count_env_vars(shell->env);
	ft_quicksort(env_array, 0, count - 1);
	while (++i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_array[i]->key, STDOUT_FILENO);
		if (env_array[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_array[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (SUCCESS);
}

int	builtin_export(t_shell *shell, t_ast *ast)
{
	t_ast	*cur;

	if (!shell || !shell->gc)
		return (ERROR);
	cur = ast;
	if (!cur)
		return (display_export_vars(shell));
	if (cur->value[0] == '-')
	{
		error_invalid_option("export", cur->value,
			"export [name[=value] ...] or export -p");
		return (handle_exit_status(shell, ERROR));
	}
	while (cur)
	{
		cur->args = value_to_args(shell->gc, cur->value);
		if (is_valid_key(cur->args) && process_export_arg(shell, cur->args))
			shell->exit_status = 0;
		else
			shell->exit_status = 1;
		cur = cur->next;
	}
	return (SUCCESS);
}
