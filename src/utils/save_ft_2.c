/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ft_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:48:01 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:02:55 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	safe_fork(t_shell *shell)
{
	pid_t	pid;

	if (!shell)
	{
		perror("minishell: safe_fork");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
	}
	return (pid);
}

void	save_close_pipe_fds(t_pipe_data *data)
{
	save_close(&data->pipe_fd[0]);
	save_close(&data->pipe_fd[1]);
}

int	save_getcwd(char **buffer, char *cmd_name)
{
	char	temp_buf[PATH_MAX];
	char	*pwd_env;

	if (!buffer)
		return (ERROR);
	if (*buffer)
		*buffer = free_s(*buffer);
	*buffer = getcwd(NULL, 0);
	if (*buffer)
		return (SUCCESS);
	if (getcwd(temp_buf, PATH_MAX) != NULL)
	{
		*buffer = ft_strdup(temp_buf);
		if (*buffer)
			return (SUCCESS);
	}
	pwd_env = getenv("PWD");
	if (pwd_env)
	{
		*buffer = ft_strdup(pwd_env);
		if (*buffer)
			return (SUCCESS);
	}
	print_errno(cmd_name, "cannot determine current directory", errno);
	return (ERROR);
}

int	save_access(char *path, int type, char *cmd_name)
{
	if (!path)
		return (ERROR);
	if (access(path, type) != 0)
		return (print_errno(cmd_name, path, errno));
	return (SUCCESS);
}

int	save_stat(char *path, char *cmd_name)
{
	struct stat	path_stat;

	if (!path)
		return (ERROR);
	if (stat(path, &path_stat) != 0)
		return (print_errno(cmd_name, path, errno));
	return (SUCCESS);
}
