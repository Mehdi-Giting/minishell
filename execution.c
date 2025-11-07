/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/11/07 07:26:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	run_command(t_cmd *cmd, char **envp)
{
	pid_t	child;
	char	*path;
	int		status;
	
	child = fork();
	if (child < 0)
	{
		perror("fork");
		return (1);
	}
	if (child == 0)
	{
		path = find_in_path(cmd->argv[0]);
		if (!path)
			exit (127);
		execve(path, cmd->argv, envp);
		perror("execve");
		free(path);
		exit(126);
	}
	else
	{
		waitpid(child, &status, 0);
		return (WEXITSTATUS(status));
	}
}

int	execute_command(t_cmd *cmd, char **envp)
{
	int	status;

	if (cmd->is_builtin)
	{
		//implement built in
	}
	else
	{
		//run the command with fork
		status = run_command(cmd, envp);
	}
	return (status);
}
