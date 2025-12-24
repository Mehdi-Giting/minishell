/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/24 11:45:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_empty_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && (!tokens[i][0]))
		i++;
	return (i);
}

void	execute_child_command(t_cmd *cmd, char **my_env)
{
	char	*path;
	int		i;

	if (apply_redirections(cmd->redirections, my_env))
		exit(1);
	i = skip_empty_tokens(cmd->tokens);
	if (!cmd->tokens[i])
		exit(0);
	path = resolve_command_path(cmd->tokens[i]);
	if (!path)
		exit(127);
	execve(path, &cmd->tokens[i], my_env);
	perror("execve");
	free(path);
	exit(126);
}

static void	handle_child_signals(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else
			write(1, "\n", 1);
	}
}

int	execute_simple_command(t_cmd *cmd, char **my_env)
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
		execute_child_command(cmd, my_env);
	}
	waitpid(child, &status, 0);
	handle_child_signals(status);
	setup_signals();
	return (get_signal_exit_code(status));
}
