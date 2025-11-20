/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/11/20 17:19:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	child_command(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_in_path(cmd->argv[0]);
	if (!path)
		exit (127);
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	exit(126);
}

int	run_command(t_cmd *cmd, char **envp)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (1);
	}
	if (child == 0)
	{
		apply_redirections(cmd->redirections);
		child_command(cmd, envp);
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_command(t_cmd *cmd, char **envp)
{
	int	status;

	if (cmd->is_builtin)
	{
		//implement built in
	}
	else if (cmd->next)
	{
		execute_pipeline(cmd, envp);
		status = 0;
	}
	else
		status = run_command(cmd, envp);
	return (status);
}
