/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/10 10:46:23 by marvin           ###   ########.fr       */
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

	ignore_signals();
	child = fork();
	if (child == -1)
	{
		perror("fork");
		setup_signals();
		return (1);
	}
	if (child == 0)
	{
		default_signals();
		apply_redirections(cmd->redirections);
		child_command(cmd, my_env);
	}
	waitpid(child, &status, 0);
	if (WIFSIGNALED(status))
	{
        if (WTERMSIG(status) == SIGQUIT)
            write(2, "Quit (core dumped)\n", 19);
        else
            write(1, "\n", 1);
	}
	setup_signals();
	return (get_signal_exit_code(status));
}

int	execute_command(t_cmd *cmd, char ***my_env)
{
	int	status;

	if (cmd->is_builtin)
		status = exec_builtin(cmd, my_env);
    else if (cmd->next)
        status = execute_pipeline(cmd, *my_env);
    else
		status = run_command(cmd, *my_env);
	g_last_exit_code = status;
	return (status);
}
