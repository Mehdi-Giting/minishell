/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:16:34 by marvin            #+#    #+#             */
/*   Updated: 2025/12/19 23:53:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_files(t_redir *current)
{
	int	fd;

	if (current->type == R_HEREDOC)
		return (0);
	if (current->type == R_IN)
		fd = open(current->file, O_RDONLY);
	else if (current->type == R_OUT)
		fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == R_APPEND)
		fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd < 0)
	{
		perror(current->file);
		return (1);
	}
	if (current->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_heredoc(t_redir *redir, char **env)
{
	int	fd;

	fd = handle_heredoc(redir, env);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirections, char **env)
{
	t_redir	*current;

	current = redirections;
	while (current)
	{
		if (current->type == R_HEREDOC)
		{
			if (apply_heredoc(current, env))
				return (1);
		}
		else
		{
			if (open_files(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
