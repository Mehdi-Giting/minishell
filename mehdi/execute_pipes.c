/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 09:23:35 by marvin           ###   ########.fr       */
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
	int		i;
	//char	**saved_tokens;

	default_signals();
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
	if (apply_redirections(current->redirections))
		exit(1);
	i = 0;
	while (current->tokens[i] && (!current->tokens[i][0]))
		i++;
	if (!current->tokens[i])
		exit(0);
	if (current->is_builtin)
	{
		//saved_tokens = current->tokens;
		current->tokens = &current->tokens[i];
		exit(exec_builtin_with_redirections(current, &my_env));
	}
	else
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
	pid_t	last_pid;
	pid_t	wpid;
	int		status;
	int		last_status;

	current = cmds;
	p_r = -1;
	last_pid = -1;
	ignore_signals();
	while (current)
	{
		fd_manager(current, pipe_fd);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			child_processe(current, p_r, pipe_fd, my_env);
		else
		{
			parrent_processe(current, &p_r, pipe_fd);
			if (!current->next)
				last_pid = pid;
		}
		current = current->next;
	}
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == last_pid)
			last_status = status;
	}
	setup_signals();
	return (get_signal_exit_code(last_status));
}
