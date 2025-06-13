/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:17:18 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:03:22 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file(char *path)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

int	is_directory(char *path, char *cmd_name)
{
	struct stat	path_stat;

	if (!path)
		return (ERROR);
	if (stat(path, &path_stat) != 0)
	{
		return (print_errno(cmd_name, path, -1));
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		return (print_errno(cmd_name, path, ENOTDIR));
	}
	return (SUCCESS);
}

int	is_symlink(char *path, char *cmd_name)
{
	struct stat	path_stat;
	struct stat	link_stat;

	if (!path)
		return (ERROR);
	if (lstat(path, &path_stat) != 0)
	{
		return (ERROR);
	}
	if (S_ISLNK(path_stat.st_mode))
	{
		if (stat(path, &link_stat) != 0)
		{
			return (print_errno(cmd_name, path, -1));
		}
		return (SUCCESS);
	}
	return (ERROR);
}
