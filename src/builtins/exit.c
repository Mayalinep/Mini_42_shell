/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:47:59 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 16:23:57 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
	i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	compare_strings(char *str, char *limit)
{
	int	i;

	if (!str || !limit)
		return (ERROR);
	i = 0;
	while (str[i])
	{
		if (str[i] > limit[i])
			return (1);
		if (str[i] < limit[i])
			return (-1);
	i++;
	}
	return (0);
}

static bool	is_number_too_large(char *str)
{
	size_t	len;
	char	*limit;

	limit = "9223372036854775807";
	if (str[0] == '+')
		str++;
	else if (str[0] == '-')
	{
		str++;
		limit = "9223372036854775808";
	}
	while (str[0] == '0')
		str++;
	len = ft_strlen(str);
	if (len > ft_strlen(limit))
		return (true);
	if (len == ft_strlen(limit))
		return (compare_strings(str, limit) > 0);
	return (false);
}

int	builtin_exit(t_shell *shell, t_ast *ast)
{
	int		status;
	long	exit_code;
	char	*arg;

	status = shell->exit_status;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!ast)
	{
		shell->is_running = 0;
		return (status);
	}
	arg = ast->value;
	if (!is_valid_number(arg) || is_number_too_large(arg))
		return (handle_invalid_arg(shell));
	if (ast->next)
		return (print_error(true, "exit", NULL, "too many arguments"),
			handle_exit_status(shell, ERROR));
	exit_code = ft_atol(arg);
	status = exit_code & 0xFF;
	shell->is_running = 0;
	shell->exit_status = status;
	return (SUCCESS);
}
