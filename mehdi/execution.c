/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/08 11:22:36 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_command(t_cmd *cmd, char **my_env)
{
	char	*path;

	setup_child_signal();
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
	int		exit_code;

	setup_parent_ignore_signals();
	child = fork();
	if (child == -1)
	{
		setup_parent_signal();
		perror("fork");
		return (1);
	}
	if (child == 0)
	{
		setup_child_signal();
		apply_redirections(cmd->redirections);
		child_command(cmd, my_env);
	}
	waitpid(child, &status, 0);
	exit_code = get_exit_code_from_status(status);
	if (WIFSIGNALED(status))
        write(STDOUT_FILENO, "\n", 1);
	setup_parent_signal();
	return (exit_code);
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
	{
		status = run_command(cmd, *my_env);
	}
	return (status);
}
