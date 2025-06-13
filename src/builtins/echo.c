/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:45:47 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/08 09:47:21 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_same_char(const char *str, const char cmp)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (ERROR);
	while (str[i])
	{
		if (str[i] != cmp)
			return (ERROR);
	i++;
	}
	return (SUCCESS);
}

int	builtin_echo(t_shell *shell, t_ast *ast)
{
	bool	newline;
	t_ast	*cur;

	if (!ast || !ast->value)
		return (ft_putchar_fd('\n', STDOUT_FILENO),
			shell->exit_status = 0, SUCCESS);
	cur = ast;
	if (cur->value && cur->value[0] == '-' && is_same_char(&cur->value[1], 'n'))
	{
		newline = false;
		cur = cur->next;
	}
	else
		newline = true;
	while (cur)
	{
		ft_putstr_fd(cur->value, STDOUT_FILENO);
		cur = cur->next;
		if (cur)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (shell->exit_status = 0, SUCCESS);
}
