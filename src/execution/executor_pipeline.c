/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellabiad <ellabiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2026/01/05 16:16:32 by ellabiad         ###   ########.fr       */
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

void	execute_pipeline_child(t_cmd *all, t_cmd *cur, t_pipe_data p,
	char **env)
{
	int	i;

	default_signals();
	close_other_heredocs(all, cur);
	setup_child_fds(p.prev_read, cur, p.pipe_fd);
	if (apply_redirections(cur->redirections))
		exit(1);
	i = skip_empty_tokens(cur->tokens);
	if (!cur->tokens[i])
		exit(0);
	if (cur->is_builtin)
	{
		cur->tokens = &cur->tokens[i];
		exit(exec_builtin_with_fds(cur, &env, i));
	}
	else
		execute_child_command(cur, env);
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
	t_cmd		*current;
	t_pipe_data	p;
	pid_t		pid;
	pid_t		last_pid;

	current = cmds;
	p.prev_read = -1;
	last_pid = -1;
	ignore_signals();
	while (current)
	{
		setup_pipe(current, p.pipe_fd);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), setup_signals(), 1);
		if (pid == 0)
			execute_pipeline_child(cmds, current, p, my_env);
		cleanup_parent_fds(current, &p.prev_read, p.pipe_fd);
		if (!current->next)
			last_pid = pid;
		current = current->next;
	}
	return (wait_for_pipeline(last_pid));
}
