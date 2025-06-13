/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:25:03 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:02:34 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_paths_array(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*check_absolute_path(char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (command);
}

static char	*search_in_paths(char **paths, char *command)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			break ;
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_paths_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_shell *shell, char *command)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!command)
		return (NULL);
	result = check_absolute_path(command);
	if (result != command)
		return (result);
	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, command);
	if (!result)
		free_paths_array(paths);
	return (result);
}
