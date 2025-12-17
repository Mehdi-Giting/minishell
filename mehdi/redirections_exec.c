/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:16:34 by marvin            #+#    #+#             */
/*   Updated: 2025/12/17 17:47:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_redirections(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == R_IN)
			fd = open(r->file, O_RDONLY);
		else if (r->type == R_OUT)
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(r->file);
			return (1);
		}
		close(fd);
		r = r->next;
	}
	return (0);
}

// Nouvelle fonction : valide sans modifier les fd

// int validate_all_redirections(t_redir *redirections)
// {
//     t_redir *current = redirections;
//     int fd;
    
//     while (current)
//     {
//         if (current->type == R_IN)
//             fd = open(current->file, O_RDONLY);
//         else if (current->type == R_OUT)
//             fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         else if (current->type == R_APPEND)
//             fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         else
//             continue; // R_HEREDOC déjà géré
            
//         if (fd < 0)
//         {
//             perror(current->file);
//             return (1);
//         }
//         close(fd);
//         current = current->next;
//     }
//     return (0);
// }

// Ensuite, apply_redirections reste comme avant

static int	open_files(t_redir *current)
{
	int	fd;

	if (current->type == R_IN)
		fd = open(current->file, O_RDONLY);
	else if (current->type == R_OUT)
		fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == R_APPEND)
		fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	apply_redirections(t_redir *redirections)
{
	t_redir	*current;

	current = redirections;
	while (current)
	{
		if (open_files(current))
			return (1);
		current = current->next;
	}
	return (0);
}

