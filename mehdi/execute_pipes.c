/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2025/12/08 11:36:58 by mehdi            ###   ########.fr       */
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

int	execute_pipeline(t_cmd *cmds, char **my_env)
{
	t_cmd	*current;
	int		p_r;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		last_exit_code;
	int		signaled;
	int		sigquit_received;

	current = cmds;
	p_r = -1;
	signaled = 0;
	setup_parent_ignore_signals();
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
		{
		    setup_child_signal();
			child_processe(current, p_r, pipe_fd, my_env);
		}
		else
			parrent_processe(current, &p_r, pipe_fd);
		current = current->next;
	}
    while (wait(&status) > 0)
	{
        last_exit_code = get_exit_code_from_status(status);
        if (WIFSIGNALED(status))
		{
            signaled = 1;
			if (WTERMSIG(status) == SIGQUIT)
            	sigquit_received = 1;
		}
	}
	if (sigquit_received)
        write(STDERR_FILENO, "Quit (core dumped)", 18);
	if (signaled)
        write(STDOUT_FILENO, "\n", 1);
	return (last_exit_code);
}
