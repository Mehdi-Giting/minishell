/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 06:22:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_command(t_cmd *cmd, char **my_env)
{
	char	*path;

	path = find_in_path(cmd->tokens[0]);
	if (!path)
		exit (127);
	execve(path, cmd->tokens, my_env);
	perror("execve");
	free(path);
	exit(126);
}

int	run_command(t_cmd *cmd, char **my_env)
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
		child_command(cmd, my_env);
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_command(t_cmd *cmd, char ***my_env)
{
	int	status;

	if (cmd->is_builtin)
	{
		status = exec_builtin(cmd, my_env);
	}
	else if (cmd->next)
	{
		execute_pipeline(cmd, *my_env);
		status = 0;
	}
	else
		status = run_command(cmd, *my_env);
	return (status);
}
