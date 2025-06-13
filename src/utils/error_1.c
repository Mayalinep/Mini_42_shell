/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:29:02 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 02:53:10 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(bool prefix, char *cmd_name, char *path, char *str)
{
	if (prefix)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
	}
}

void	error_invalid_identifier(char *cmd, char *key)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": \"", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("\": not a valid identifier\n", STDERR_FILENO);
}

void	error_invalid_option(char *cmd, char *key, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd(key[0], STDERR_FILENO);
	ft_putchar_fd(key[1], STDERR_FILENO);
	ft_putstr_fd(" : invalid option\n", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : usage : ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	print_errno(char *cmd_name, char *path, int force_errno)
{
	int	err_code;

	if (force_errno < 0)
		err_code = errno;
	else
		err_code = force_errno;
	print_error(true, cmd_name, path, NULL);
	if (err_code == ENOENT)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (err_code == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (err_code == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else if (err_code == EISDIR)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else if (err_code == EEXIST)
		ft_putstr_fd(": File exists\n", STDERR_FILENO);
	else if (err_code == ENOMEM)
		ft_putstr_fd(": Cannot allocate memory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": Error\n", STDERR_FILENO);
	return (ERROR);
}

int	handle_fork_error(t_pipe_data *data)
{
	save_close_pipe_fds(data);
	if (data->pid_left > 0)
	{
		kill(data->pid_left, SIGTERM);
		waitpid(data->pid_left, NULL, 0);
	}
	return (ERROR);
}
