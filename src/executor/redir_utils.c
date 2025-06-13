/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:03:40 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/10 20:47:51 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redir_heredocs(t_shell *shell, t_ast *ast)
{
	char	**delimiters;
	int		delimiter_count;
	int		heredoc_fd;

	if (ast->type != TOKEN_HEREDOC)
		return (SUCCESS);
	delimiters = collect_heredoc_delimiters(shell, ast, &delimiter_count);
	if (!delimiters)
		return (ERROR);
	heredoc_fd = process_heredocs_loop(shell, delimiters, delimiter_count);
	if (heredoc_fd == -1)
		return (ERROR);
	dup2(heredoc_fd, STDIN_FILENO);
	close(heredoc_fd);
	return (SUCCESS);
}
