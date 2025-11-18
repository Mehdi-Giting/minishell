/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:38:52 by marvin            #+#    #+#             */
/*   Updated: 2025/11/15 08:51:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute_pipeline(t_cmd *cmds, char **envp)
{
	t_cmd	*current;
	int		previous_read;
	int		pipe_fd[2];
	pid_t	pid;

	current = cmds;
	previous_read = -1;
	while (current)
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

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0)
		{
			if (previous_read != -1)
    			dup2(previous_read, STDIN_FILENO);
			if (current->next)
    			dup2(pipe_fd[1], STDOUT_FILENO);
		}
		
		current = current->next;
	}
}
