/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 09:21:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_command(t_cmd *cmd, char **my_env)
{
	char	*path;
	int		i;

	if (apply_redirections(cmd->redirections))
		exit(1);
	i = 0;
	while (cmd->tokens[i] && (!cmd->tokens[i][0]))
		i++;
	if (!cmd->tokens[i])
		exit(0);
	path = find_in_path(cmd->tokens[i]);
	if (!path)
		exit (127);
	execve(path, &cmd->tokens[i], my_env);
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

	if (cmd->next)
		status = execute_pipeline(cmd, *my_env);
	else if (cmd->is_builtin)
		status = exec_builtin_with_redirections(cmd, my_env);
	else
		status = run_command(cmd, *my_env);
	return (status);
}