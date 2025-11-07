/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:16:34 by marvin            #+#    #+#             */
/*   Updated: 2025/11/07 23:26:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	open_files(t_redir *current)
{
	int	fd;

	if (current->type == R_IN)
		fd = open(current->file, O_RDONLY);
	if (current->type == R_OUT)
		fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (current->type == R_APPEND)
		fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	if (current->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirections)
{
	t_redir	*current;

	current = redirections;
	while (current)
	{
		open_files(current);
		current = current->next;
	}
}
