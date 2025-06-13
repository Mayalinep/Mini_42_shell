/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:47:15 by lylaurol          #+#    #+#             */
/*   Updated: 2025/06/09 00:02:04 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_heredocs(t_ast *ast)
{
	int		count;
	t_ast	*current;

	count = 0;
	current = ast;
	while (current && current->type == TOKEN_HEREDOC)
	{
		count++;
		current = current->left;
	}
	return (count);
}

void	fill_delimiters(char **delimiters, t_ast *ast, int count)
{
	t_ast	*current;
	int		i;

	current = ast;
	i = count - 1;
	while (current && current->type == TOKEN_HEREDOC && i >= 0)
	{
		delimiters[i] = current->right->value;
		current = current->left;
		i--;
	}
	delimiters[count] = NULL;
}

char	**collect_heredoc_delimiters(t_shell *shell, t_ast *ast, int *count)
{
	char	**delimiters;

	*count = count_heredocs(ast);
	if (*count == 0)
		return (NULL);
	delimiters = gc_calloc(shell->gc, (*count + 1), sizeof(char *));
	if (!delimiters)
		return (NULL);
	fill_delimiters(delimiters, ast, *count);
	return (delimiters);
}

t_ast	*find_command_after_heredocs(t_ast *ast)
{
	t_ast	*current;

	current = ast;
	while (current && current->type == TOKEN_HEREDOC)
		current = current->left;
	return (current);
}
