/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 05:53:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//p_r stand for previous read, to please the norm i had to squiz the name

#include "../include/minishell.h"

static void	fd_manager(t_cmd *current, int	*pipe_fd)
{
	if (current->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

static void	child_processe(t_cmd *current, int p_r, int *pipe_fd, char **my_env)
{
	if (p_r != -1)
		dup2(p_r, STDIN_FILENO);
	if (current->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (p_r != -1)
		close(p_r);
	if (current->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	apply_redirections(current->redirections);
	child_command(current, my_env);
}

static void	parrent_processe(t_cmd *current, int *p_r, int *pipe_fd)
{
	if (*p_r != -1)
		close(*p_r);
	if (current->next)
	{
		close(pipe_fd[1]);
		*p_r = pipe_fd[0];
	}
	else
		*p_r = -1;
}

void	execute_pipeline(t_cmd *cmds, char **my_env)
{
	t_cmd	*current;
	int		p_r;
	int		pipe_fd[2];
	pid_t	pid;

	current = cmds;
	p_r = -1;
	while (current)
	{
		fd_manager(current, pipe_fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			child_processe(current, p_r, pipe_fd, my_env);
		else
			parrent_processe(current, &p_r, pipe_fd);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
}
