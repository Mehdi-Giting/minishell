/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 19:29:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipe(t_cmd *current, int *pipe_fd)
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

void	setup_child_fds(int prev_read, t_cmd *current, int *pipe_fd)
{
	if (prev_read != -1)
		dup2(prev_read, STDIN_FILENO);
	if (current->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (prev_read != -1)
		close(prev_read);
	if (current->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	execute_pipeline_child(t_cmd *cmd, int p_r, int *pfd, char **env)
{
	int	i;

	default_signals();
	setup_child_fds(p_r, cmd, pfd);
	if (apply_redirections(cmd->redirections, env))
		exit(1);
	i = skip_empty_tokens(cmd->tokens);
	if (!cmd->tokens[i])
		exit(0);
	if (cmd->is_builtin)
	{
		cmd->tokens = &cmd->tokens[i];
		exit(execute_builtin_with_redirections(cmd, &env));
	}
	else
		execute_child_command(cmd, env);
}

void	cleanup_parent_fds(t_cmd *current, int *prev_read, int *pipe_fd)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (current->next)
	{
		close(pipe_fd[1]);
		*prev_read = pipe_fd[0];
	}
	else
		*prev_read = -1;
}

int	execute_pipeline(t_cmd *cmds, char **my_env)
{
	t_cmd	*current;
	int		prev_read;
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	last_pid;

	current = cmds;
	prev_read = -1;
	last_pid = -1;
	ignore_signals();
	while (current)
	{
		setup_pipe(current, pipe_fd);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			execute_pipeline_child(current, prev_read, pipe_fd, my_env);
		cleanup_parent_fds(current, &prev_read, pipe_fd);
		if (!current->next)
			last_pid = pid;
		current = current->next;
	}
	return (wait_for_pipeline(last_pid));
}
