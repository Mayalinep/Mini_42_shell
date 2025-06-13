/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ft_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:40:16 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:03:02 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_close(int *fd)
{
	if (fd && *fd != -1)
	{
		if (close(*fd) == -1)
			ft_putendl_fd("Error closing file descriptor", 2);
		*fd = -1;
	}
}

static int	check_file_for_opening(t_shell *shell, char *filename, int flags)
{
	(void)shell;
	if (!filename || !*filename)
	{
		print_error(true, NULL, NULL, "No such file or directory");
		return (ERROR);
	}
	if ((flags & O_ACCMODE) == O_RDONLY && !(flags & O_CREAT))
	{
		if (is_file(filename) != SUCCESS)
			return (ERROR);
		if (save_access(filename, R_OK, NULL) != SUCCESS)
			return (ERROR);
	}
	else if ((flags & O_ACCMODE) != O_RDONLY)
	{
		if (is_directory(filename, NULL))
			return (ERROR);
		if (save_access(filename, F_OK, NULL) == SUCCESS
			&& save_access(filename, W_OK, NULL) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	save_open(t_shell *shell, char *filename, int flags, mode_t mode)
{
	int	fd;

	if (!shell || !filename)
	{
		print_error(true, NULL, NULL, "Invalid arguments for save_open");
		return (-1);
	}
	if (check_file_for_opening(shell, filename, flags) == ERROR)
		return (-1);
	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		print_errno(NULL, filename, errno);
		return (-1);
	}
	if (gc_add_fd(shell->gc, fd) != SUCCESS)
	{
		save_close(&fd);
		print_error(true, NULL, NULL, "Failed to register fd");
		return (-1);
	}
	return (fd);
}

int	save_descriptor(int fd)
{
	int	saved_fd;

	saved_fd = dup(fd);
	if (saved_fd == -1)
	{
		perror("minishell: dup");
		return (-1);
	}
	return (saved_fd);
}
