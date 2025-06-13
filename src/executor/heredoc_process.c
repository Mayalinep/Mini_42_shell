/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:39:54 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 22:45:56 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_heredoc_line(int write_fd, char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		close(write_fd);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(line) == ft_strlen(delimiter) && ft_strncmp(line, delimiter,
			ft_strlen(delimiter)) == 0)
	{
		free(line);
		return (1);
	}
	ft_putendl_fd(line, write_fd);
	free(line);
	return (0);
}

void	heredoc_child_process(int pipe_fd[2], char *delimiter)
{
	setup_heredoc_signals();
	close(pipe_fd[0]);
	if (!delimiter || ft_strlen(delimiter) == 0)
	{
		fprintf(stderr, "minishell: heredoc: empty delimiter\n");
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (process_heredoc_line(pipe_fd[1], delimiter))
			break ;
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

pid_t	create_heredoc_child(int pipe_fd[2], char *delimiter)
{
	pid_t	pid;

	if (!delimiter || ft_strlen(delimiter) == 0)
	{
		fprintf(stderr, "minishell: heredoc: empty delimiter\n");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
		heredoc_child_process(pipe_fd, delimiter);
	return (pid);
}

int	process_single_heredoc(t_shell *shell, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		return (perror("minishell: pipe"), ERROR);
	}
	if (gc_add_heredoc(shell->gc, pipe_fd[0], pipe_fd[1]) == ERROR)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	pid = create_heredoc_child(pipe_fd, delimiter);
	if (pid == -1)
		return (-1);
	g_signal_pid = pid;
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	g_signal_pid = 0;
	return (handle_heredoc_signals(status, shell, pipe_fd[0]));
}
