/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/09 02:10:21 by marvin           ###   ########.fr       */
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
	{
	    // printf("DEBUG: Calling exec_builtin()\n");
		status = exec_builtin(cmd, my_env);
	}
    else if (cmd->next)
    {
        // printf("DEBUG: Calling execute_pipeline()\n");
        status = execute_pipeline(cmd, *my_env);
    }
    else
    {
        // printf("DEBUG: Calling run_command()\n");
        status = run_command(cmd, *my_env);
    }
	// printf("%d\n", cmd->is_builtin);
	g_last_exit_code = status;
	return (status);
}
